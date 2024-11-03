#pragma once

#ifdef RYANJXDLL_EXPORTS
#define RYANDLL_API __declspec(dllexport)
#else
#define RYANDLL_API __declspec(dllimport)
#endif

extern "C" RYANDLL_API int InjectDll(HWND hWnd, DWORD threadId);
extern "C" RYANDLL_API int UnmapDll(HWND hWnd);

extern HINSTANCE           hDll;
extern const UINT WM_HOOKEX;
extern const UINT WM_HOOK_WRITE;
extern LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam);
