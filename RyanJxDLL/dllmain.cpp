#include "pch.h"
#include "RyanJxDLL.h"
#include <string>
#include <Windows.h>
#include "RLogger.h"

const UINT WM_HOOK_WRITE = RegisterWindowMessage(L"WM_HOOK_WRITE");
const UINT WM_HOOKEX = RegisterWindowMessage(L"WM_HOOKEX_RK");
const UINT WM_RYANJX = RegisterWindowMessage(L"WM_RYANJX");

HINSTANCE           hDll;
WNDPROC				OldWndProc = NULL;
LRESULT CALLBACK	NewWndProc(HWND, UINT, WPARAM, LPARAM);
BOOL bHooked = 0;
#define pCW ((CWPSTRUCT*)lParam)

typedef void(__cdecl* _exeChatScript)(const char* szScript);

RLogger logger;


BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		logger.writeLog("DLL attached");
        hDll = (HINSTANCE)hModule;
        DisableThreadLibraryCalls(hDll);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	HWND hVLWnd = pCW->hwnd;
	HHOOK hHook = (HHOOK)pCW->wParam;
	
	logger.writeLog("HookProc running");
	if ((pCW->message == WM_HOOKEX) && pCW->lParam)
	{
		logger.writeLog("Unhooking & LoadLibrary");
		UnhookWindowsHookEx(hHook);
		if (bHooked)
			goto END;
		char lib_name[MAX_PATH];
		GetModuleFileNameA(hDll, lib_name, MAX_PATH);
		if (!LoadLibraryA(lib_name))
			goto END;
		OldWndProc = (WNDPROC)SetWindowLongPtr(hVLWnd, GWLP_WNDPROC, (LONG)NewWndProc);
		if (OldWndProc == NULL && false) {
			logger.writeLog("Call FreeLibrary 1");
			FreeLibrary(hDll);
		}
		else
		{
			logger.writeLog("Inject DLL succecced");
			bHooked = TRUE;
		}
	}
	else if (pCW->message == WM_HOOKEX)
	{
		logger.writeLog("Un-Hooking");
		UnhookWindowsHookEx(hHook);
		if (!bHooked)
			goto END;
		if (!SetWindowLong(hVLWnd, GWLP_WNDPROC, (LONG)OldWndProc))
			goto END;
		logger.writeLog("Call FreeLibrary 2");
		FreeLibrary(hDll);
		bHooked = FALSE;
	}
END:
	return CallNextHookEx(hHook, nCode, wParam, lParam);
}

LRESULT CALLBACK NewWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_RYANJX)
	{
		logger.writeLog("Handling RyanJxUI message...");
		DWORD dwGBaseAddr = reinterpret_cast<DWORD>(GetModuleHandleA("game.exe"));
		_exeChatScript exeChatScript = (_exeChatScript)(dwGBaseAddr + 0x140c0);
		std::string szScript1;
		switch (lParam)
		{
		case 1:
			szScript1 = "Chat('CH_NEARBY','Hi,ÙreceivedÙmessageÙ1')";
			exeChatScript(szScript1.c_str());
			break;
		case 2:
			szScript1 = "Chat('CH_NEARBY','Hi,ÙreceivedÙmessageÙ2')";
			exeChatScript(szScript1.c_str());
			break;
		default:
			return 0;
		}
	}
	return CallWindowProc(OldWndProc, hWnd, uMsg, wParam, lParam);
}