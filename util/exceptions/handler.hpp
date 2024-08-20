#pragma once

#include "Zydis/Zydis.h"
namespace insight::exceptions {
    class exception_error {
    public:
        exception_error(int t, std::string_view r) : m_type(t), m_reason(r) {}
        std::string what() {
            return m_reason.data();
        }
        int type() {
            return m_type;
        }
        bool operator()() {
            return !what().empty();
        }
    protected:
        int m_type{};
        std::string_view m_reason{};
    };

    class exception_type {
    public:
        exception_type(uint32_t code, const char* str) : m_code(code), m_string(str) {}
        std::string str() {
            return m_string.data();
        }
        uint32_t code() {
            return m_code;
        }
        bool operator()() {
            return !str().empty();
        }
    protected:
        uint32_t m_code{};
        std::string_view m_string{};
    };

    class exception_context {
    public:
        exception_context(EXCEPTION_POINTERS* exception)
            : m_record(*exception->ExceptionRecord), m_context(*exception->ContextRecord), m_type(m_record.ExceptionInformation[0]), m_death_address(m_record.ExceptionInformation[1])
        {
            m_code = m_record.ExceptionCode;
            m_exception_address = (uint64_t)m_record.ExceptionAddress;
        }
    public:
        void print_registers() {
            LOG(WARNING) << "RAX: 0x" << std::hex << m_context.Rax << " || RSI: 0x" << m_context.Rsi;
            LOG(WARNING) << "RBX: 0x" << std::hex << m_context.Rbx << " || RDI: 0x" << m_context.Rdi;
            LOG(WARNING) << "RCX: 0x" << std::hex << m_context.Rcx << " || RBP: 0x" << m_context.Rbp;
            LOG(WARNING) << "RDX: 0x" << std::hex << m_context.Rdx << " || RSP: 0x" << m_context.Rsp;
            LOG(WARNING) << "R8:  0x" << std::hex << m_context.R8 << " || R9:  0x" << m_context.R9;
            LOG(WARNING) << "R10: 0x" << std::hex << m_context.R10 << " || R11: 0x" << m_context.R11;
            LOG(WARNING) << "R12: 0x" << std::hex << m_context.R12 << " || R13: 0x" << m_context.R13;
            LOG(WARNING) << "R14: 0x" << std::hex << m_context.R14 << " || R15: 0x" << m_context.R15;
        }
    public:
        uint32_t m_code{};
        uint64_t m_exception_address{};
        EXCEPTION_RECORD& m_record;
        CONTEXT& m_context;
        uint64_t m_type{};
        uint64_t m_death_address{};
        std::string m_file_offset{};
    };

    extern bool attempt_stack_recovery(PEXCEPTION_POINTERS exception_info);

#define PAIR(v) exception_type(v, #v)

    inline std::array<exception_type, 62> g_exception_types{
        PAIR(STATUS_WAIT_0),
            PAIR(STATUS_ABANDONED_WAIT_0),
            PAIR(STATUS_USER_APC),
            PAIR(STATUS_TIMEOUT),
            PAIR(STATUS_PENDING),
            PAIR(DBG_EXCEPTION_HANDLED),
            PAIR(DBG_CONTINUE),
            PAIR(STATUS_SEGMENT_NOTIFICATION),
            PAIR(STATUS_FATAL_APP_EXIT),
            PAIR(DBG_REPLY_LATER),
            PAIR(DBG_TERMINATE_THREAD),
            PAIR(DBG_TERMINATE_PROCESS),
            PAIR(DBG_CONTROL_C),
            PAIR(DBG_PRINTEXCEPTION_C),
            PAIR(DBG_RIPEXCEPTION),
            PAIR(DBG_CONTROL_BREAK),
            PAIR(DBG_PRINTEXCEPTION_WIDE_C),
            PAIR(DBG_COMMAND_EXCEPTION),
            PAIR(STATUS_GUARD_PAGE_VIOLATION),
            PAIR(STATUS_DATATYPE_MISALIGNMENT),
            PAIR(STATUS_BREAKPOINT),
            PAIR(STATUS_SINGLE_STEP),
            PAIR(STATUS_LONGJUMP),
            PAIR(STATUS_UNWIND_CONSOLIDATE),
            PAIR(DBG_EXCEPTION_NOT_HANDLED),
            PAIR(STATUS_ACCESS_VIOLATION),
            PAIR(STATUS_IN_PAGE_ERROR),
            PAIR(STATUS_INVALID_HANDLE),
            PAIR(STATUS_INVALID_PARAMETER),
            PAIR(STATUS_NO_MEMORY),
            PAIR(STATUS_ILLEGAL_INSTRUCTION),
            PAIR(STATUS_NONCONTINUABLE_EXCEPTION),
            PAIR(STATUS_INVALID_DISPOSITION),
            PAIR(STATUS_ARRAY_BOUNDS_EXCEEDED),
            PAIR(STATUS_FLOAT_DENORMAL_OPERAND),
            PAIR(STATUS_FLOAT_DIVIDE_BY_ZERO),
            PAIR(STATUS_FLOAT_INVALID_OPERATION),
            PAIR(STATUS_FLOAT_OVERFLOW),
            PAIR(STATUS_FLOAT_STACK_CHECK),
            PAIR(STATUS_FLOAT_UNDERFLOW),
            PAIR(STATUS_INTEGER_DIVIDE_BY_ZERO),
            PAIR(STATUS_INTEGER_OVERFLOW),
            PAIR(STATUS_PRIVILEGED_INSTRUCTION),
            PAIR(STATUS_STACK_OVERFLOW),
            PAIR(STATUS_DLL_NOT_FOUND),
            PAIR(STATUS_ORDINAL_NOT_FOUND),
            PAIR(STATUS_ENTRYPOINT_NOT_FOUND),
            PAIR(STATUS_CONTROL_C_EXIT),
            PAIR(STATUS_DLL_INIT_FAILED),
            PAIR(STATUS_CONTROL_STACK_VIOLATION),
            PAIR(STATUS_FLOAT_MULTIPLE_FAULTS),
            PAIR(STATUS_REG_NAT_CONSUMPTION),
            PAIR(STATUS_HEAP_CORRUPTION),
            PAIR(STATUS_STACK_BUFFER_OVERRUN),
            PAIR(STATUS_INVALID_CRUNTIME_PARAMETER),
            PAIR(STATUS_ASSERTION_FAILURE),
            PAIR(STATUS_ENCLAVE_VIOLATION),
            PAIR(STATUS_INTERRUPTED),
            PAIR(STATUS_THREAD_NOT_RUNNING),
            PAIR(STATUS_ALREADY_REGISTERED),
            PAIR(STATUS_SXS_EARLY_DEACTIVATION),
            PAIR(STATUS_SXS_INVALID_DEACTIVATION)
    };

    inline std::array<exception_error, 3> g_exception_error_reasons{
        exception_error(0, "a attempt to read an invalid address"),
            exception_error(1, "a attempt to write to an invalid address"),
            exception_error(8, "an data exception prevention (DEP)")
    };

    extern std::string get_exception_type(ULONG_PTR type);
    extern LONG CALLBACK on_exception_callback(PEXCEPTION_POINTERS exception_info);
    extern bool on_exception_callback_try_except(PEXCEPTION_POINTERS exception_info);
    extern LONG CALLBACK exception_handler(PEXCEPTION_POINTERS exception_info);
    extern LONG CALLBACK unhandled_exception_handler(PEXCEPTION_POINTERS exception_info);

    inline PVOID vec_excep_handler_handle{};

    extern void init_exception_handler();
    extern void uninit_exception_handler();
}