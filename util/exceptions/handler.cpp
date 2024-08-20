#include "handler.hpp"
#include "disassembler.hpp"
#include "StackWalker/StackWalker.hpp"
#include <HDE/hde64.h>
#include "auth/instance.hpp"

class stack_walker : public StackWalker {
public:
	stack_walker() : StackWalker() {}
	stack_walker(ExceptType exType) : StackWalker(exType) {}
	virtual void OnOutput(LPCSTR szText);
	virtual void OnLoadModule(LPCSTR img, LPCSTR mod, DWORD64 baseAddr, DWORD size, DWORD result, LPCSTR symType, LPCSTR pdbName, ULONGLONG fileVersion);
	virtual void OnSymInit(LPCSTR szSearchPath, DWORD symOptions, LPCSTR szUserName);
	virtual void OnDbgHelpErr(LPCSTR szFuncName, DWORD gle, DWORD64 addr);
	virtual void OnCallstackEntry(CallstackEntryType eType, CallstackEntry& entry);
};

void stack_walker::OnOutput(LPCSTR szText) {
	std::string text(szText);
	LOG(WARNING) << text.substr(0, text.size() - 1);
}
void stack_walker::OnLoadModule(LPCSTR img, LPCSTR mod, DWORD64 baseAddr, DWORD size, DWORD result, LPCSTR symType, LPCSTR pdbName, ULONGLONG fileVersion) {
#ifdef DEBUG_MODE
	StackWalker::OnLoadModule(img, mod, baseAddr, size, result, symType, pdbName, fileVersion);
#endif
}
void stack_walker::OnSymInit(LPCSTR szSearchPath, DWORD symOptions, LPCSTR szUserName) {
#ifdef DEBUG_MODE
	StackWalker::OnSymInit(szSearchPath, symOptions, szUserName);
#endif
}
void stack_walker::OnDbgHelpErr(LPCSTR szFuncName, DWORD gle, DWORD64 addr) {
	//std::string offsetStr{ base::util::modules::getModuleNameFromAddress<u64>(addr) };
	LOG(WARNING) << "Error (" << gle << ") in " << szFuncName << " at 0x" << std::hex << addr;
}

void stack_walker::OnCallstackEntry(CallstackEntryType eType, CallstackEntry& entry) {
	return StackWalker::OnCallstackEntry(eType, entry);
	std::string offsetStr{ std::format("{}.dll+0x{:X}", entry.moduleName, entry.offset) };

	if (entry.lineFileName[0]) {
		if (entry.name[0]) {
			LOG(WARNING) << entry.lineFileName << " L" << entry.lineNumber << ": " << entry.name << " (" << offsetStr << ")";
		}
	}
	else {
		if (entry.name[0]) {
			LOG(WARNING) << entry.name << " (" << offsetStr << ")";
		}
		else {
			LOG(WARNING) << offsetStr;
		}
	}

	LOG(WARNING) << offsetStr;

}


inline stack_walker g_stackwalker;
namespace insight::exceptions {
	uint8_t get_instruction_length(uint8_t* code) {
		hde64s hde{};
		//Most light to most heavy on CPU cycles. It's pretty much a system of what can handle what at what speed
		if (uint8_t len = hde64_disasm((void*)code, &hde); len) {
			return len;
		}
		else if (uint8_t len = x64::get_instruction_length(code); len) {
			return len;
		}
		else {
			ZyanU64 opcodeAddress{ (uint64_t)code };
			ZydisDisassembledInstruction instruction{};
			if (ZYAN_SUCCESS(ZydisDisassembleIntel(ZYDIS_MACHINE_MODE_LONG_64, opcodeAddress, reinterpret_cast<void*>(opcodeAddress), 32, &instruction))) {
				return instruction.info.length;
			}
		}
		return NULL;
	}
	bool attempt_stack_recovery(PEXCEPTION_POINTERS exceptionInfo) {
		auto& ctx = exceptionInfo->ContextRecord;
		if (const auto len = get_instruction_length(reinterpret_cast<uint8_t*>(ctx->Rip)); len) {
			ctx->Rip += len;
			return true;
		}
		return false;
	}
	std::string get_exception_type(ULONG_PTR type) {
		if (g_exception_error_reasons[type]()) {
			return g_exception_error_reasons[type].what();
		}
		return "unknown";
	}
	LONG CALLBACK on_exception_callback(PEXCEPTION_POINTERS exceptionInfo) {
		stack_walker sw(StackWalker::AfterExcept);
		exception_context ctx{ exceptionInfo };
		if (auth::g_key_level == 3) {
			LOG(INFO) << "Dumping registers...";
			g_stackwalker.ShowCallstack(GetCurrentThread(), &ctx.m_context);
			ctx.print_registers();
		}
		if (!ctx.m_file_offset.empty()) {
			switch (ctx.m_code) {
			case CONTROL_C_EXIT: { return EXCEPTION_CONTINUE_EXECUTION; } break;
			case EXCEPTION_BREAKPOINT: { return EXCEPTION_CONTINUE_EXECUTION; } break;
			case EXCEPTION_ACCESS_VIOLATION: {
				auto exceptionTypeStr = get_exception_type(ctx.m_type);
				auto exceptionName = g_exception_error_reasons[ctx.m_code]() ? g_exception_error_reasons[ctx.m_code].what() : std::format("0x{:X}", ctx.m_code);
				if (auth::g_key_level == 3) {
					LOG(WARNING) << "The game suffered a fatal exception, you may need to restart the game. (" << exceptionName << " at " << ctx.m_file_offset
						<< ", reason of " << exceptionName << " was " << exceptionTypeStr << (ctx.m_type != 8 && exceptionName != "unknown" ? "" : std::format("0x{:X}", ctx.m_death_address)) << ")";
				}
			} break;
			default: {
				auto exceptionName = g_exception_error_reasons[ctx.m_code]() ? g_exception_error_reasons[ctx.m_code].what() : std::format("0x{:X}", ctx.m_code);
				if (auth::g_key_level == 3) {
					LOG(WARNING) << "The game suffered an exception of unknown severity, you may need to restart the game. (" << exceptionName << " at " << ctx.m_file_offset
						<< ", reason of exception is unknown)";
				}
			}
			}
		}

		if (auth::g_key_level == 3) {
			LOG(INFO) << "Dumping registers...";
			g_stackwalker.ShowCallstack(GetCurrentThread(), &ctx.m_context);
			ctx.print_registers();
		}
	
		if (attempt_stack_recovery(exceptionInfo)) {
			return EXCEPTION_CONTINUE_EXECUTION;
		}
		else {
			if (auth::g_key_level == 3) {
				LOG(WARNING) << "Failed stack recovery, re-attempting exception search for a valid point in the stack...";
			}
		}
		return EXCEPTION_CONTINUE_SEARCH;
	}
	bool on_exception_callback_try_except(PEXCEPTION_POINTERS exceptionInfo) {
		if (on_exception_callback(exceptionInfo) != EXCEPTION_CONTINUE_EXECUTION)
			return false;
		return true;
	}
	LONG CALLBACK exception_handler(PEXCEPTION_POINTERS exceptionInfo) {
		return on_exception_callback(exceptionInfo);
	}
	LONG CALLBACK unhandled_exception_handler(PEXCEPTION_POINTERS exceptionInfo) {
		return on_exception_callback(exceptionInfo);
	}
	void init_exception_handler() {
#ifndef DISABLE_EXCEPTION_HANDLER
		vec_excep_handler_handle = AddVectoredExceptionHandler(FALSE, PVECTORED_EXCEPTION_HANDLER(exception_handler));
		SetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER(unhandled_exception_handler));
#endif
	}
	void uninit_exception_handler() {
		if (vec_excep_handler_handle)
			RemoveVectoredExceptionHandler(vec_excep_handler_handle);
	}
}