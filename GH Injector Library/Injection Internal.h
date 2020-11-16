#pragma once

#include "Start Routine.h"

#define ALIGN_UP(X, A) (X + (A - 1)) & (~(A - 1))

ALIGN struct INJECTION_FUNCTION_TABLE
{
	ALIGN WIN32_FUNC_LOCAL(LoadLibraryExW);
	ALIGN NT_FUNC_LOCAL(LdrLoadDll);
	ALIGN NT_FUNC_LOCAL(LdrpLoadDll);

	ALIGN WIN32_FUNC_LOCAL(GetLastError);

	ALIGN NT_FUNC_LOCAL(memmove);
	ALIGN NT_FUNC_LOCAL(RtlZeroMemory);
	ALIGN NT_FUNC_LOCAL(RtlFreeHeap);

	ALIGN NT_FUNC_LOCAL(RtlRbRemoveNode);

	ALIGN NT_FUNC_LOCAL(NtProtectVirtualMemory);

	ALIGN NT_FUNC_LOCAL(LdrpModuleBaseAddressIndex);
	ALIGN NT_FUNC_LOCAL(LdrpMappingInfoIndex);
	ALIGN NT_FUNC_LOCAL(LdrpHeap);

	INJECTION_FUNCTION_TABLE();
};

ALIGN struct INJECTION_DATA_INTERNAL
{
	ALIGN HINSTANCE	hRet;
	ALIGN DWORD		LastError;

	ALIGN DWORD				Flags;
	ALIGN INJECTION_MODE	Mode;

	ALIGN UNICODE_STRING	ModuleFileName;
	ALIGN wchar_t			Path[MAX_PATH];
	
	ALIGN INJECTION_FUNCTION_TABLE f;
};

DWORD InjectDLL(const wchar_t * szDllFile, HANDLE hTargetProc, INJECTION_MODE Mode, LAUNCH_METHOD Method, DWORD Flags, HINSTANCE & hOut, DWORD Timeout, ERROR_DATA & error_data);

#ifdef _WIN64

ALIGN_86 struct INJECTION_FUNCTION_TABLE_WOW64
{
	ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LoadLibraryExW);
	ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrLoadDll);
	ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrpLoadDll);

	ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(GetLastError);

	ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(memmove);
	ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(RtlZeroMemory);
	ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(RtlFreeHeap);

	ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(RtlRbRemoveNode);

	ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(NtProtectVirtualMemory);

	ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrpModuleBaseAddressIndex);
	ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrpMappingInfoIndex);
	ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrpHeap);

	INJECTION_FUNCTION_TABLE_WOW64();
};

ALIGN_86 struct INJECTION_DATA_INTERNAL_WOW64
{
	ALIGN_86 DWORD hRet;
	ALIGN_86 DWORD LastError;

	ALIGN_86 DWORD			Flags;
	ALIGN_86 INJECTION_MODE	Mode;

	ALIGN_86 UNICODE_STRING32	ModuleFileName;
	ALIGN_86 wchar_t			Path[MAX_PATH];

	ALIGN_86 INJECTION_FUNCTION_TABLE_WOW64 f;
};

DWORD InjectDLL_WOW64(const wchar_t * szDllFile, HANDLE hTargetProc, INJECTION_MODE Mode, LAUNCH_METHOD Method, DWORD Flags, HINSTANCE & hOut, DWORD Timeout, ERROR_DATA & error_data);

#endif