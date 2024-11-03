#pragma once
#pragma comment(lib, "user32.lib")

#include <unordered_map>
#include <Windows.h>
#include "GameWnd.h"
#include "RLogger.h"
#include <vector>

const UINT WM_HOOK_WRITE = RegisterWindowMessage(L"WM_HOOK_WRITE");
const UINT WH_RYANJX = RegisterWindowMessage(L"WM_RYANJX");

class GameWnd;

class GameWndManager
{
public:
	std::unordered_map<DWORD, GameWnd*> gameWnds;
	RLogger* logger;

	GameWndManager(RLogger* logger);
	void RefreshGameData();
	GameWnd* getGameWnd(DWORD pid);
	GameWnd* getGameWnd(System::String^ pid);
	void notifyDeath();
};

