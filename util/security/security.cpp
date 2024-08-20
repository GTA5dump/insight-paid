#include "security.hpp"
#include <curl/curl.h>
#include <winternl.h>
#include <DbgHelp.h>
#include <TlHelp32.h>
#include <vector>
#include <winternl.h>
#include <winnt.h>
#include "util/http/http.hpp"
#include <auth/instance.hpp>
#include "auth/VMP/VMProtectSDK.h"

#pragma comment(lib, "dbghelp.lib")
#pragma warning(push)
#pragma warning(disable: 4244)
using NtCloseTypedef = NTSTATUS(*)(HANDLE);
using NtQueryInformationProcessTypedef = NTSTATUS(*)(HANDLE, UINT, PVOID, ULONG, PULONG);
using NtQuerySystemInformationTypedef = NTSTATUS(*)(ULONG, PVOID, ULONG, PULONG);

extern "C" NTSTATUS NtFlushInstructionCache(HANDLE, PVOID, SIZE_T);
extern "C" NTSTATUS NtOpenThread(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, CLIENT_ID*);
extern "C" NTSTATUS NtSuspendThread(HANDLE, PULONG);
extern "C" NTSTATUS NtResumeThread(HANDLE, PULONG);
extern "C" NTSTATUS NtAllocateVirtualMemory(HANDLE, PVOID*, ULONG, PSIZE_T, ULONG, ULONG);
extern "C" NTSTATUS NtFreeVirtualMemory(HANDLE, PVOID*, PSIZE_T, ULONG);

typedef NTSTATUS(NTAPI* _NtQuerySystemInformation)(
	ULONG SystemInformationClass,
	PVOID SystemInformation,
	ULONG SystemInformationLength,
	PULONG ReturnLength
	);

typedef NTSTATUS(NTAPI* _NtDuplicateObject)(
	HANDLE SourceProcessHandle,
	HANDLE SourceHandle,
	HANDLE TargetProcessHandle,
	PHANDLE TargetHandle,
	ACCESS_MASK DesiredAccess,
	ULONG Attributes,
	ULONG Options
	);
typedef NTSTATUS(NTAPI* _NtQueryObject)(
	HANDLE ObjectHandle,
	ULONG ObjectInformationClass,
	PVOID ObjectInformation,
	ULONG ObjectInformationLength,
	PULONG ReturnLength
	);


typedef struct _SYSTEM_HANDLE
{
	ULONG ProcessId;
	BYTE ObjectTypeNumber;
	BYTE Flags;
	USHORT Handle;
	PVOID Object;
	ACCESS_MASK GrantedAccess;
} SYSTEM_HANDLE, * PSYSTEM_HANDLE;

typedef struct _CODE_CRC32
{
	PVOID         m_va;
	DWORD         m_size;
	DWORD         m_crc32;
}CODE_CRC32;

typedef struct _SYSTEM_HANDLE_INFORMATION
{
	ULONG HandleCount;
	SYSTEM_HANDLE Handles[1];
} SYSTEM_HANDLE_INFORMATION, * PSYSTEM_HANDLE_INFORMATION;

typedef enum err_code
{
	err_success,
	err_enum_process_modules_failed,
	err_size_too_small,
	err_mod_name_not_found,
	err_mod_query_failed,
	err_create_file_failed,
	err_create_file_mapping_failed,
	err_create_file_mapping_already_exists,
	err_map_file_failed,
	err_mem_deprotect_failed,
	err_mem_reprotect_failed,
	err_text_section_not_found,
	err_file_path_query_failed
} err_code;

typedef enum suspend_resume_type
{
	srt_suspend,
	srt_resume
} suspend_resume_type, * psuspend_resume_type;

typedef struct suspend_resume_info
{
	ULONG current_pid;
	ULONG current_tid;
	suspend_resume_type type;
} suspend_resume_info, * psuspend_resume_info;

typedef struct wrk_system_process_information
{
	ULONG next_entry_offset;
	ULONG number_of_threads;
	LARGE_INTEGER spare_li1;
	LARGE_INTEGER spare_li2;
	LARGE_INTEGER spare_li3;
	LARGE_INTEGER create_time;
	LARGE_INTEGER user_time;
	LARGE_INTEGER kernel_time;
	UNICODE_STRING image_name;
	KPRIORITY base_priority;
	HANDLE unique_process_id;
	HANDLE inherited_from_unique_process_id;
	ULONG handle_count;
	ULONG session_id;
	ULONG_PTR page_directory_base;
	SIZE_T peak_virtual_size;
	SIZE_T virtual_size;
	ULONG page_fault_count;
	SIZE_T peak_working_set_size;
	SIZE_T working_set_size;
	SIZE_T quota_peak_paged_pool_usage;
	SIZE_T quota_paged_pool_usage;
	SIZE_T quota_peak_non_paged_pool_usage;
	SIZE_T quota_non_paged_pool_usage;
	SIZE_T pagefile_usage;
	SIZE_T peak_pagefile_usage;
	SIZE_T private_page_count;
	LARGE_INTEGER read_operation_count;
	LARGE_INTEGER write_operation_count;
	LARGE_INTEGER other_operation_count;
	LARGE_INTEGER read_transfer_count;
	LARGE_INTEGER write_transfer_count;
	LARGE_INTEGER other_transfer_count;
	SYSTEM_THREAD_INFORMATION threads[1];
} wrk_system_process_information, * pwrk_system_process_information;

typedef enum wrk_memory_information_class
{
	memory_basic_information
} wrk_memory_information_class, * pwrk_memory_information_class;

typedef struct object_type_information
{
	UNICODE_STRING type_name;
	ULONG total_number_of_handles;
	ULONG total_number_of_objects;
} object_type_information, * pobject_type_information;

typedef struct object_all_information
{
	ULONG number_of_objects;
	object_type_information object_type_information[1];
} object_all_information, * pobject_all_information;

#pragma pack(push, 1)
struct DbgUiRemoteBreakinPatch
{
	WORD  push_0;
	BYTE  push;
	DWORD CurrentPorcessHandle;
	BYTE  mov_eax;
	DWORD TerminateProcess;
	WORD  call_eax;
};
#pragma pack(pop)
namespace insight {

#pragma region AntiDebug
	__forceinline int RemoteDebuggerPresentAPI()
	{
		auto dbg_present = 0;

		CheckRemoteDebuggerPresent(GetCurrentProcess(), &dbg_present);

		return dbg_present;
	}

	__forceinline int NtQueryInformationProcessDebugFlags()
	{
		const auto debug_flags = 0x1f;

		const auto query_info_process = reinterpret_cast<NtQueryInformationProcessTypedef>(GetProcAddress(
			GetModuleHandleW(L"ntdll.dll"), "NtQueryInformationProcess"));

		auto debug_inherit = 0;

		const auto status = query_info_process(GetCurrentProcess(), debug_flags, &debug_inherit,
			sizeof(DWORD),
			nullptr);

		if (status == 0x00000000 && debug_inherit == 0)
		{
			return 1;
		}

		return 0;
	}

	__forceinline int NtQueryInformationProcessDebugObject()
	{
		const auto debug_object_handle = 0x1e;

		const auto query_info_process = reinterpret_cast<NtQueryInformationProcessTypedef>(GetProcAddress(
			GetModuleHandleW(L"ntdll.dll"), "NtQueryInformationProcess"));

		HANDLE debug_object = nullptr;

		const auto information_length = sizeof(ULONG) * 2;

		const auto status = query_info_process(GetCurrentProcess(), debug_object_handle, &debug_object,
			information_length,
			nullptr);

		if (status == 0x00000000 && debug_object)
		{
			return 1;
		}

		return 0;
	}

	__forceinline bool heapDebuggerFlags() // https://anti-debug.checkpoint.com/techniques/debug-flags.html#manual-checks-heap-protection
	{
		PPEB pPeb = (PPEB)__readgsqword(0x60);
		PVOID pHeapBase = (PVOID)(*(PDWORD_PTR)((PBYTE)pPeb + 0x30));
		DWORD dwHeapFlagsOffset = 0x70;
		DWORD dwHeapForceFlagsOffset = 0x74;

		PDWORD pdwHeapFlags = (PDWORD)((PBYTE)pHeapBase + dwHeapFlagsOffset);
		PDWORD pdwHeapForceFlags = (PDWORD)((PBYTE)pHeapBase + dwHeapForceFlagsOffset);
		return (*pdwHeapFlags & ~HEAP_GROWABLE) || (*pdwHeapForceFlags != 0);
	}

	__forceinline bool HeapProtectionFlag()
	{
		PROCESS_HEAP_ENTRY HeapEntry = { 0 };
		do
		{
			if (!HeapWalk(GetProcessHeap(), &HeapEntry))
				return false;
		} while (HeapEntry.wFlags != PROCESS_HEAP_ENTRY_BUSY);

		PVOID pOverlapped = (PBYTE)HeapEntry.lpData + HeapEntry.cbData;
		return ((DWORD)(*(PDWORD)pOverlapped) == 0xABABABAB);
	}

	__forceinline bool PEBBeingDebugged()
	{
		PPEB pPeb = (PPEB)__readgsqword(0x60);
		return pPeb->BeingDebugged;
	}

	__forceinline bool IsDebuggerPresentPatched() // https://github.com/grossekette/artemis/blob/main/Artemis.cpp
	{
		HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
		if (!hKernel32)
			return false;

		FARPROC pIsDebuggerPresent = GetProcAddress(hKernel32, "IsDebuggerPresent");
		if (!pIsDebuggerPresent)
			return false;

		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (INVALID_HANDLE_VALUE == hSnapshot)
			return false;

		PROCESSENTRY32W ProcessEntry;
		ProcessEntry.dwSize = sizeof(PROCESSENTRY32W);

		if (!Process32FirstW(hSnapshot, &ProcessEntry))
			return false;

		bool bDebuggerPresent = false;
		HANDLE hProcess = NULL;
		DWORD dwFuncBytes = 0;
		const DWORD dwCurrentPID = GetCurrentProcessId();
		do
		{
			__try
			{
				if (dwCurrentPID == ProcessEntry.th32ProcessID)
					__leave;

				hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessEntry.th32ProcessID);
				if (NULL == hProcess)
					__leave;

				if (!ReadProcessMemory(hProcess, pIsDebuggerPresent, &dwFuncBytes, sizeof(DWORD), NULL))
					__leave;

				if (dwFuncBytes != *(PDWORD)pIsDebuggerPresent)
				{
					bDebuggerPresent = true;
					__leave;
				}
			}
			__finally
			{
				if (hProcess)
					CloseHandle(hProcess);
				else
				{

				}
			}
		} while (Process32NextW(hSnapshot, &ProcessEntry));

		if (hSnapshot)
			CloseHandle(hSnapshot);

		return bDebuggerPresent;
	}

	__forceinline void PatchRemoteBreakin() // https://github.com/grossekette/artemis/blob/main/Artemis.cpp
	{
		HMODULE hNtdll = GetModuleHandleA("ntdll.dll");
		if (!hNtdll)
			return;

		FARPROC pDbgUiRemoteBreakin = GetProcAddress(hNtdll, "DbgUiRemoteBreakin");
		if (!pDbgUiRemoteBreakin)
			return;

		HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
		if (!hKernel32)
			return;

		FARPROC pTerminateProcess = GetProcAddress(hKernel32, "TerminateProcess");
		if (!pTerminateProcess)
			return;

		DbgUiRemoteBreakinPatch patch = { 0 };
		patch.push_0 = '\x6A\x00';
		patch.push = '\x68';
		patch.CurrentPorcessHandle = 0xFFFFFFFF;
		patch.mov_eax = '\xB8';
		patch.TerminateProcess = reinterpret_cast<DWORD_PTR>(pTerminateProcess);;
		patch.call_eax = '\xFF\xD0';

		DWORD dwOldProtect;
		if (!VirtualProtect(pDbgUiRemoteBreakin, sizeof(DbgUiRemoteBreakinPatch), PAGE_READWRITE, &dwOldProtect))
			return;

		::memcpy_s(pDbgUiRemoteBreakin, sizeof(DbgUiRemoteBreakinPatch),
			&patch, sizeof(DbgUiRemoteBreakinPatch));
		VirtualProtect(pDbgUiRemoteBreakin, sizeof(DbgUiRemoteBreakinPatch), dwOldProtect, &dwOldProtect);
	}

	__forceinline bool CheckHardwareBP()
	{
		CONTEXT ctx;
		ZeroMemory(&ctx, sizeof(CONTEXT));
		ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;

		if (!GetThreadContext(GetCurrentThread(), &ctx))
			return false;

		return ctx.Dr0 || ctx.Dr1 || ctx.Dr2 || ctx.Dr3;
	}
#pragma endregion

	bool security::has_hooks()
	{
#ifndef DEV
		VMProtectBegin("REAL");
#endif // !DEV
		auto fc = &curl_wrapper::set_write_function;
		auto fc2 = &curl_wrapper::set_url;
		auto fc3 = &curl_wrapper::set_header;
		auto fc4 = &curl_easy_setopt;
		auto fc5 = &auth::authenticate;
		auto fc6 = &auth::authenticate_from_json;
		auto fc7 = &auth::heartbeat;
		auto fc8 = &auth::api::heartbeat;
		auto fc9 = &auth::api::initialize;
		auto fc10 = &auth::debugger_checks;
		auto fc11 = &auth::authenticate;
		auto fc12 = &auth::authenticate_from_json;
		auto fc13 = &auth::get_access_level;
		auto fc14 = &auth::heartbeat;
		auto fc15 = &auth::initialize;
		auto fc16 = &auth::authed::set_authed;
		auto fc17 = &auth::authed::is;
		std::vector<void*> addys{
			(void*)GetProcAddress(GetModuleHandleW(L"kernel32.dll"), "GetModuleHandleA"),		//
			(void*)GetProcAddress(GetModuleHandleW(L"user32.dll"), "FindWindowA"),				//
			(void*)GetProcAddress(GetModuleHandleW(L"Advapi32.dll"), "RegOpenKeyA"),			//
			(void*)GetProcAddress(GetModuleHandleW(L"Advapi32.dll"), "RegQueryValueExA"),		//  THEMIDIE
			(void*)GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "NtSetInformationThread"),	//
			(void*)GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "NtQueryVirtualMemory"),		//
			(void*)GetProcAddress(GetModuleHandleW(L"ws2_32.dll"), "recv"),
			(void*)GetProcAddress(GetModuleHandleW(L"kernel32.dll"), "GetVolumeInformationA"),
			(void*)GetProcAddress(GetModuleHandleW(L"kernel32.dll"), "TerminateProcess"),
			(void*)GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "NtQuerySystemInformation"),
			(void*&)fc,
			(void*&)fc2,
			(void*&)fc3,
			(void*&)fc4,
			(void*&)fc5,
			(void*&)fc6,
			(void*&)fc7,
			(void*&)fc8,
			(void*&)fc9,
			(void*&)fc10,
			(void*&)fc11,
			(void*&)fc12,
			(void*&)fc13,
			(void*&)fc14,
			(void*&)fc15,
			(void*&)fc16,
			(void*&)fc17
		};

		for (auto address : addys) {
			if (address) {
				while (*(BYTE*)(address) == 0x90) { // while instruction == NOP 
					address = (void*)((uintptr_t)address + 0x1);
					Sleep(1);
				}

				if (*(BYTE*)address == 0xE9 || *(BYTE*)address == 0xC3) { // JMP / RET
					return true;
				}
			}
		}

#ifndef DEV
		VMProtectEnd();
#endif // !DEV

		return false;
	}

	bool security::is_begin_debugged()
	{
		return RemoteDebuggerPresentAPI() || NtQueryInformationProcessDebugFlags() || NtQueryInformationProcessDebugObject() || heapDebuggerFlags() || HeapProtectionFlag() || PEBBeingDebugged() || IsDebuggerPresentPatched();
	}

	void security::anti_attach() {
		HMODULE hNtdll = GetModuleHandleA("ntdll.dll");
		if (!hNtdll)
			return;

		FARPROC pDbgBreakPoint = GetProcAddress(hNtdll, "DbgBreakPoint");
		if (!pDbgBreakPoint)
			return;

		DWORD dwOldProtect;
		if (!VirtualProtect(pDbgBreakPoint, 1, PAGE_EXECUTE_READWRITE, &dwOldProtect))
			return;

		*(PBYTE)pDbgBreakPoint = (BYTE)0xC3; // 0xC3 == RET
	}

	bool IsUsingVMWARE() {
		DWORD error = ERROR_SUCCESS;
		DWORD acpiDataSize = 0;
		BYTE* acpiData = NULL;
		DWORD bytesWritten = 0;

		acpiDataSize = GetSystemFirmwareTable('ACPI', 'TEPH', NULL, 0);

		acpiData = (BYTE*)HeapAlloc(GetProcessHeap(), 0, acpiDataSize);
		if (!acpiData) {
			error = ERROR_OUTOFMEMORY;
			HeapFree(GetProcessHeap(), 0, acpiData);
			return false;
		}

		bytesWritten = GetSystemFirmwareTable('ACPI', 'TEPH', acpiData, acpiDataSize);

		if (bytesWritten != acpiDataSize) {
			error = ERROR_INVALID_DATA;
			HeapFree(GetProcessHeap(), 0, acpiData);
			return false;
		}
		std::string haystack(acpiData, acpiData + bytesWritten);
		return haystack.find("VMWARE") != std::string::npos;
	}

	bool HasVm3dgl() {
		WIN32_FIND_DATAW findFileData;
		HANDLE file = FindFirstFileW(
			L"C:\\Windows\\System32\\vm3dgl.dll",
			&findFileData
		);
		return file != INVALID_HANDLE_VALUE;
	}

	bool HasSuspiciousRegistery() {
		HKEY hkResult;
		LONG key = RegOpenKeyExW(
			HKEY_LOCAL_MACHINE,
			L"System\\ControlSet001\\Services\\VMTools",
			0,
			KEY_QUERY_VALUE,
			&hkResult
		);
		return key == ERROR_SUCCESS;
	}

	bool HasSuspiciousSpecs() {
		SYSTEM_INFO lpSystemInfo;
		GetSystemInfo(&lpSystemInfo);
		DWORD numberOfProcessors = lpSystemInfo.dwNumberOfProcessors;
		if (numberOfProcessors < 2)
			return true;

		// Check RAM
		MEMORYSTATUSEX memoryStatus;
		memoryStatus.dwLength = sizeof(memoryStatus);
		GlobalMemoryStatusEx(&memoryStatus);
		DWORD RAMMB = memoryStatus.ullTotalPhys / 1024 / 1024;
		if (RAMMB < 2048)
			return true;
		return false;
	}


	bool security::is_on_vm()
	{
		return HasSuspiciousSpecs() || HasSuspiciousRegistery() || HasVm3dgl() || IsUsingVMWARE();
	}
	
#pragma region txtSectionIntegrity

	int GetAllModule(std::vector<LPVOID>& modules) {
		MODULEENTRY32W mEntry;
		memset(&mEntry, 0, sizeof(mEntry));
		mEntry.dwSize = sizeof(MODULEENTRY32);

		DWORD curPid = GetCurrentProcessId();

		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, NULL);
		if (Module32FirstW(hSnapshot, &mEntry)) {
			do {
				modules.emplace_back(mEntry.modBaseAddr);
			} while (Module32NextW(hSnapshot, &mEntry));
		}

		CloseHandle(hSnapshot);

		if (modules.empty()) {
			return -1;
		}

		return 0;
	}

	int GetTextSectionInfo(LPVOID lpModBaseAddr, PSECTIONINFO info) {
		PIMAGE_NT_HEADERS pNtHdr = ImageNtHeader(lpModBaseAddr);
		PIMAGE_SECTION_HEADER pSectionHeader = (PIMAGE_SECTION_HEADER)(pNtHdr + 1);

		LPVOID lpTextAddr = NULL;
		DWORD dwSizeOfRawData = NULL;

		for (int i = 0; i < pNtHdr->FileHeader.NumberOfSections; ++i) {
			char* name = (char*)pSectionHeader->Name;

			if (!strcmp(name, ".text")) {
				info->lpVirtualAddress = (LPVOID)((DWORD64)lpModBaseAddr + pSectionHeader->VirtualAddress);
				info->dwSizeOfRawData = pSectionHeader->SizeOfRawData;
				break;
			}

			++pSectionHeader;
		}

		if (info->dwSizeOfRawData == NULL) {
			return -1;
		}

		return 0;
	}

	DWORD64 security::hash_section(LPVOID lpSectionAddress, DWORD dwSizeOfRawData) {
		DWORD64 hash = 0;
		BYTE* str = (BYTE*)lpSectionAddress;
		for (int i = 0; i < dwSizeOfRawData; ++i, ++str) {
			if (*str) {
				hash = *str + (hash << 6) + (hash << 16) - hash;
			}
		}

		return hash;
	}
#pragma endregion

	std::vector<HASHSET> security::get_modules_section_hash()
	{
		std::vector<LPVOID> modules; GetAllModule(modules);
		std::vector<HASHSET> hashes; hashes.reserve(modules.size());

		for (auto& module : modules) {
			SECTIONINFO info;
			GetTextSectionInfo(module, &info);

			DWORD64 dwRealHash = hash_section(info.lpVirtualAddress, info.dwSizeOfRawData);
			hashes.emplace_back(HASHSET{ dwRealHash, info });
		}

		return hashes;
	}
	// wrote by chat gpt4 & me dawg !!

	void security::check_debugger_break() {
		__try {
			DebugBreak();
			Sleep(5000);
			exit(0);
		}
		__except (GetExceptionCode() == EXCEPTION_BREAKPOINT ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
		}
	}

	void security::output_debug() {
		SetLastError(0);
		OutputDebugStringA("kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger ");
		if (GetLastError() != 0) {
			Sleep(5000);
			exit(0);
		}
	}

	bool SetThreadsState(bool IsResume) {
		HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
		if (hSnapShot == INVALID_HANDLE_VALUE) {
			//DbgPrint((TEXT("CreateToolhelp32Snapshot failed, Error: %d\n"), GetLastError()));
			return false;
		}

		THREADENTRY32 ThreadEntry = { 0 };
		ThreadEntry.dwSize = sizeof(ThreadEntry);
		DWORD ThreadId = GetCurrentThreadId();
		DWORD ProcessId = GetCurrentProcessId();
		if (!Thread32First(hSnapShot, &ThreadEntry)) {
			//DbgPrint((TEXT("Thread32First failed, Error: %d\n"), GetLastError()));
			CloseHandle(hSnapShot);
			return false;
		}

		do {
			if (ProcessId == ThreadEntry.th32OwnerProcessID && ThreadId != ThreadEntry.th32ThreadID) {
				HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, ThreadEntry.th32ThreadID);
				if (hThread != NULL) {
					if (IsResume) {
						ResumeThread(hThread);
					}
					else {
						SuspendThread(hThread);
					}
					CloseHandle(hThread);
				}
			}
		} while (Thread32Next(hSnapShot, &ThreadEntry));

		CloseHandle(hSnapShot);
		return true;
	}

	void PrintModulesInformation() {
		NTQUERYINFORMATIONPROCESS* pfnNtQueryInformationProcess =
			(NTQUERYINFORMATIONPROCESS*)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "NtQueryInformationProcess");
		if (pfnNtQueryInformationProcess != NULL) {
			PROCESS_BASIC_INFORMATION PBI = { 0 };
			DWORD ReturnLength = 0;
			if (NT_SUCCESS(pfnNtQueryInformationProcess(GetCurrentProcess(), ProcessBasicInformation, &PBI, sizeof(PBI), &ReturnLength))) {
				PLDR_MODULE LdrModule = NULL;
				PLIST_ENTRY Head = PBI.PebBaseAddress->Ldr->InMemoryOrderModuleList.Flink;
				PLIST_ENTRY Current = Head;

				do {
					LdrModule = (PLDR_MODULE)CONTAINING_RECORD(Current, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);
					Current = Current->Flink;
				} while (Current != Head);
			}
		}
	}

	void AdjustModuleReferenceCount(HMODULE hModule) {
		NTQUERYINFORMATIONPROCESS* pfnNtQueryInformationProcess =
			(NTQUERYINFORMATIONPROCESS*)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "NtQueryInformationProcess");
		if (pfnNtQueryInformationProcess != NULL) {
			PROCESS_BASIC_INFORMATION PBI = { 0 };
			DWORD ReturnLength = 0;
			if (NT_SUCCESS(pfnNtQueryInformationProcess(GetCurrentProcess(), ProcessBasicInformation, &PBI, sizeof(PBI), &ReturnLength))) {
				PLDR_MODULE LdrModule = NULL;
				PLIST_ENTRY Head = PBI.PebBaseAddress->Ldr->InMemoryOrderModuleList.Flink;
				PLIST_ENTRY Current = Head;

				do {
					LdrModule = (PLDR_MODULE)CONTAINING_RECORD(Current, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

					// The LoadCount of DLLs that are static linked is -1, that kind of DLLs can't be freed
					// by FreeLibrary. So I modify that LoadCount to 1 in case that this DLL is static linked.
					if (LdrModule->BaseAddress == hModule) {
						// Add the reference count of DLLs that this module relies on
						LoadLibraryW(LdrModule->BaseDllName.Buffer);
						LdrModule->LoadCount = 1;
						break;
					}
					Current = Current->Flink;
				} while (Current != Head);
			}
		}
	}

	bool unload_module(HMODULE hModule, LPVOID lpNewBaseAddr, ULONG_PTR SizeOfImage)
	{
		LPVOID lpBaseOfDll = (LPVOID)hModule;
		MEMCPY* pfnMemCpy = (MEMCPY*)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "memcpy");
		VIRTUALALLOC* pfnVirtualAlloc = (VIRTUALALLOC*)GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "VirtualAlloc");
		bool ret = false;

		if (!FreeLibrary(hModule)) {
			// DbgPrint((TEXT("FreeLibrary for the module failed, Error: %d\n"), GetLastError()));
		}

		// After FreeLibrary, we can't use any functions whose addresses are not retrieved before.
		// And the strings are invalid also.
		LPVOID OriBaseAddr = pfnVirtualAlloc(lpBaseOfDll, SizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		if (OriBaseAddr == NULL) {
			// DbgPrint((TEXT("pfnVirtualAlloc for OriBaseAddr failed, Error: %d\n"), GetLastError()));
		}
		else if (OriBaseAddr != lpBaseOfDll) {
			// DbgPrint((TEXT("OriBaseAddr is not equal to lpBaseOfDll\n")));
		}
		else {
			pfnMemCpy(OriBaseAddr, lpNewBaseAddr, SizeOfImage);
			ret = true;
		}
		return ret;
	}


	void security::hide_module(HMODULE hModule, bool DeleteAfter) {
		MODULEINFO ModuleInfo = { 0 };
		if (!GetModuleInformation(GetCurrentProcess(), hModule, &ModuleInfo, sizeof(ModuleInfo))) {
			// DbgPrint((TEXT("GetModuleInformation failed, Error: %d\n"), GetLastError()));
			return;
		}

		LPVOID lpNewBaseAddr = VirtualAlloc(NULL, ModuleInfo.SizeOfImage,
			MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		if (lpNewBaseAddr == NULL) {
			// DbgPrint((TEXT("VirtualAlloc for lpNewBaseAddr failed, Error: %d\n"), GetLastError()));
			return;
		}

		memcpy(lpNewBaseAddr, ModuleInfo.lpBaseOfDll, ModuleInfo.SizeOfImage);
		UNLOADMODULE* pfnUnloadModule = (UNLOADMODULE*)((ULONG_PTR)unload_module
			- (ULONG_PTR)ModuleInfo.lpBaseOfDll + (ULONG_PTR)lpNewBaseAddr);


		AdjustModuleReferenceCount(hModule);



		TCHAR FileName[MAX_PATH] = { 0 };
		bool HasFileName = false;
		if (DeleteAfter) {
			if (!GetModuleFileName(hModule, FileName, _countof(FileName))) {
				return;
			}
			else {
				HasFileName = true;
			}
		}

		SetThreadsState(false);
		// Jump to the new space, and free the original dll in the new space
		if (!pfnUnloadModule(hModule, lpNewBaseAddr, ModuleInfo.SizeOfImage)) {
			// DbgPrint((TEXT("UnloadModule failed, Error: %d\n"), GetLastError()));
		}
		// Jump back to the original space
		SetThreadsState(true);

		//Print(TEXT("\n---------------------------------------------\n"));
		//Print(TEXT("Check the modules after FreeLibrary is called\n"));
		//PrintModulesInformation();

		if (!VirtualFree(lpNewBaseAddr, 0, MEM_DECOMMIT)) {
			// DbgPrint((TEXT("VirtualFree for lpNewBaseAddr failed, Error: %d\n"), GetLastError()));
		}

		if (HasFileName) {
			if (!DeleteFile(FileName)) {
				// DbgPrint((TEXT("DeleteFile failed, Error: %d\n"), GetLastError()));
			}
		}
	}

	bool security::run() {
		static FileID fileID;
		std::vector<std::string> iconRes = fileID.iconCheck();
		if (iconRes.size() != 0) {
			for (int i = 0; i < iconRes.size(); i++) {
				
			}
		}
		std::vector<std::string> hostRes = fileID.hostCheck();
		if (hostRes.size() != 0) {
			for (int i = 0; i < hostRes.size(); i++) {

			}
		}
		std::vector<std::string> driverRes = fileID.driverCheck();
		if (driverRes.size() != 0) {
			for (int i = 0; i < driverRes.size(); i++) {

			}
		}
		std::vector<std::string> stringRes = fileID.stringCheck();
		if (stringRes.size() != 0) {
			for (int i = 0; i < stringRes.size(); i++) {
				LOG(WARNING) << stringRes[i];
			}
		}
		std::vector<std::string> sigRes = fileID.sigCheck();
		if (sigRes.size() != 0) {
			for (int i = 0; i < sigRes.size(); i++) {
			}
		}
		return 0;
	}

}
#pragma warning(pop)

WORD debugger::GetProcessIdFromName(LPCTSTR szProcessName)
{
	PROCESSENTRY32 pe32;
	HANDLE hSnapshot = NULL;
	SecureZeroMemory(&pe32, sizeof(PROCESSENTRY32));

	// We want a snapshot of processes
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	// Check for a valid handle, in this case we need to check for
	// INVALID_HANDLE_VALUE instead of NULL
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		return 0;
	}

	// Now we can enumerate the running process, also
	// we can't forget to set the PROCESSENTRY32.dwSize member
	// otherwise the following functions will fail
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hSnapshot, &pe32) == FALSE)
	{
		// Cleanup the mess
		CloseHandle(hSnapshot);
		return 0;
	}

	// Do our first comparison
	if (StrCmpI(pe32.szExeFile, szProcessName) == 0)
	{
		// Cleanup the mess
		CloseHandle(hSnapshot);
		return pe32.th32ProcessID;
	}

	// Most likely it won't match on the first try so
	// we loop through the rest of the entries until
	// we find the matching entry or not one at all
	while (Process32Next(hSnapshot, &pe32))
	{
		if (StrCmpI(pe32.szExeFile, szProcessName) == 0)
		{
			// Cleanup the mess
			CloseHandle(hSnapshot);
			return pe32.th32ProcessID;
		}
	}

	// If we made it this far there wasn't a match, so we'll return 0
	// _tprintf(_T("\n-> Process %s is not running on this system ..."), szProcessName);

	CloseHandle(hSnapshot);
	return 0;
}

void debugger::ProcessChecker()
{
	const TCHAR* szProcesses[] = {
	_T("ollydbg.exe"),			// OllyDebug debugger
	_T("ProcessHacker.exe"),	// Process Hacker
	_T("tcpview.exe"),			// Part of Sysinternals Suite
	_T("autoruns.exe"),			// Part of Sysinternals Suite
	_T("autorunsc.exe"),		// Part of Sysinternals Suite
	_T("filemon.exe"),			// Part of Sysinternals Suite
	_T("procmon.exe"),			// Part of Sysinternals Suite
	_T("regmon.exe"),			// Part of Sysinternals Suite
	_T("procexp.exe"),			// Part of Sysinternals Suite
	_T("idaq.exe"),				// IDA Pro Interactive Disassembler
	_T("idaq64.exe"),			// IDA Pro Interactive Disassembler
	_T("ImmunityDebugger.exe"), // ImmunityDebugger
	_T("Wireshark.exe"),		// Wireshark packet sniffer
	_T("dumpcap.exe"),			// Network traffic dump tool
	_T("HookExplorer.exe"),		// Find various types of runtime hooks
	_T("ImportREC.exe"),		// Import Reconstructor
	_T("Scylla_x64.exe"),
	_T("PETools.exe"),			// PE Tool
	_T("LordPE.exe"),			// LordPE
	_T("SysInspector.exe"),		// ESET SysInspector
	_T("proc_analyzer.exe"),	// Part of SysAnalyzer iDefense
	_T("sysAnalyzer.exe"),		// Part of SysAnalyzer iDefense
	_T("sniff_hit.exe"),		// Part of SysAnalyzer iDefense
	_T("windbg.exe"),			// Microsoft WinDbg
	_T("joeboxcontrol.exe"),	// Part of Joe Sandbox
	_T("joeboxserver.exe"),		// Part of Joe Sandbox
	_T("joeboxserver.exe"),		// Part of Joe Sandbox
	_T("ResourceHacker.exe"),	// Resource Hacker
	_T("x32dbg.exe"),			// x32dbg
	_T("x64dbg.exe"),			// x64dbg
	_T("x64dbg.exe"),			// x64dbg
	_T("Fiddler.exe"),			// Fiddler
	_T("httpdebugger.exe"),		// Http Debugger
	};

	WORD iLength = sizeof(szProcesses) / sizeof(szProcesses[0]);
	for (int i = 0; i < iLength; i++)
	{
		TCHAR msg[256] = _T("");
		if (GetProcessIdFromName(szProcesses[i]))
		{
			utility::notification(OBFUSCATE("[Debugger] You're a retard."));
			debugger::BSOD();
		}
	}
}

bool debugger::IsDebuggerPresent()
{
	HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
	if (!hKernel32)
		return false;

	FARPROC pIsDebuggerPresent = GetProcAddress(hKernel32, "IsDebuggerPresent");
	if (!pIsDebuggerPresent)
		return false;

	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot)
		return false;

	PROCESSENTRY32W ProcessEntry;
	ProcessEntry.dwSize = sizeof(PROCESSENTRY32W);

	if (!Process32FirstW(hSnapshot, &ProcessEntry))
		return false;

	bool bDebuggerPresent = false;
	HANDLE hProcess = NULL;
	DWORD dwFuncBytes = 0;
	const DWORD dwCurrentPID = GetCurrentProcessId();
	do
	{
		__try
		{
			if (dwCurrentPID == ProcessEntry.th32ProcessID)
				continue;

			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessEntry.th32ProcessID);
			if (NULL == hProcess)
				continue;

			if (!ReadProcessMemory(hProcess, pIsDebuggerPresent, &dwFuncBytes, sizeof(DWORD), NULL))
				continue;

			if (dwFuncBytes != *(PDWORD)pIsDebuggerPresent)
			{
				bDebuggerPresent = true;
				break;
			}
		}
		__finally
		{
			if (hProcess)
				CloseHandle(hProcess);
		}
	} while (Process32NextW(hSnapshot, &ProcessEntry));

	if (hSnapshot)
		CloseHandle(hSnapshot);
	return bDebuggerPresent;
}

void debugger::IsDebuggerPresentTick()
{
	if (IsDebuggerPresent())
	{
		utility::notification(OBFUSCATE("[Debugger] You're doing something shady."));
		debugger::BSOD();
	}
}

void debugger::BSOD()
{
	typedef long (WINAPI* RtlSetProcessIsCritical)
		(BOOLEAN New, BOOLEAN* Old, BOOLEAN NeedScb);

	HMODULE ntdll = LoadLibraryA("ntdll.dll");

	if (ntdll)
	{
		auto SetProcessIsCritical = (RtlSetProcessIsCritical)GetProcAddress(ntdll, "RtlSetProcessIsCritical");

		if (SetProcessIsCritical)SetProcessIsCritical(1, 0, 0);
	}
}

std::string debugger::RandomString(std::size_t StringLength)
{
	const std::string Alphanumeric = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

	std::random_device RandomDevice;
	std::mt19937 mtGen(RandomDevice());
	std::uniform_int_distribution<> uDistribution(0, Alphanumeric.size() - 1);

	std::string LoaderName;

	for (std::size_t i = 0; i < StringLength; i++) {
		LoaderName = LoaderName + Alphanumeric[uDistribution(mtGen)];
	}

	return LoaderName;
}