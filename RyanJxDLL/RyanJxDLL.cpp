//#include <string>
#include "pch.h"
#include "RyanJxDLL.h"
#include "RLogger.h"

RLogger mlogger;

int InjectDll(HWND hWnd, DWORD threadId)
{
	if (!IsWindow(hWnd))
		return 111;

	HHOOK hHook = SetWindowsHookExW(WH_CALLWNDPROC, (HOOKPROC)HookProc, hDll, threadId);
	if (hHook == NULL)
		return 222;

	SendMessageW(hWnd, WM_HOOKEX, WPARAM(hHook), 1);
	return 333;
}

int UnmapDll(HWND hWnd)
{
	if (!IsWindow(hWnd))
		return 1;
	HHOOK hHook = SetWindowsHookExW(WH_CALLWNDPROC, (HOOKPROC)HookProc, hDll, GetWindowThreadProcessId(hWnd, NULL));
	
	if (hHook == NULL)
		return 2;
	SendMessage(hWnd, WM_HOOKEX, (WPARAM)hHook, 0);
	return 3;
}
