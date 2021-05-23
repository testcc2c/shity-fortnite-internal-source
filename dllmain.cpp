#include "stdafx.h"

#define RELATIVE_ADDR(addr, size)       ((uintptr_t)((uintptr_t)(addr) + *(PINT)((uintptr_t)(addr) + ((size) - sizeof(INT))) + (size)))

#define rva(addr, size) (reinterpret_cast<unsigned char*>(addr + *reinterpret_cast<int*>(addr + (size - 4)) + size))




void Main() {

	

	static DWORD_PTR funcGetObjectName = NULL;

	auto basemodule = GetModuleHandle(0);


	Basic::UWorld_Offset = g_Scanner->FindPattern(basemodule, skCrypt("\x48\x89\x05\x00\x00\x00\x00\x48\x8B\x8B\x00\x00\x00\x00"), skCrypt("xxx????xxx????"), 0);
	Basic::UWorld_Offset = reinterpret_cast<decltype(Basic::UWorld_Offset)>(rva(Basic::UWorld_Offset, 7)); // ((DWORD64)GetModuleHandleW(NULL) + 0x93538B0);
	
	
	
	
	 pGetBoneMatrix = g_Scanner->FindPattern(basemodule, skCrypt("\xE8\x00\x00\x00\x00\x48\x8B\x47\x30\xF3\x0F\x10\x45\x00"), skCrypt("x????xxxxxxxx?"), 0);
	pGetBoneMatrix = reinterpret_cast<decltype(pGetBoneMatrix)>(rva(pGetBoneMatrix, 5));
	


	PBYTE addr = (PBYTE)(DWORD64)GetModuleHandleW(NULL) + 0x5E24A5C;
	LOS = reinterpret_cast<decltype(LOS)>(addr);


	hkpost::hkpostexecute();
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);
//		AllocConsole();
 //   	freopen("conin$", "r", stdin);
 //   	freopen("conout$", "w", stdout);
	//    freopen("conout$", "w", stderr);
		Main();

		
	}

	return TRUE;
}
