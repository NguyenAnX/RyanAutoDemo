#pragma once

#include <Windows.h>
#include "Npc.h"
#include "ConfigState.h"
#include "GameWndManager.h"
#include <msclr/marshal_cppstd.h> // For string conversion


#define NPC_BASE	0x012C5540
#define PLAYER_INDEX_BASE 0x008E48F4
#define PLAYER_INDEX_OFFSET 0x8C44
#define NPC_SIZE	0x113B8
#define HP_OFFSET	0x1048
#define MP_OFFSET	0x1058
#define NAME_OFFSET 0x130D
#define IS_BOSS_OFFSET 0x40
#define NPC_NUM 256


class GameWndManager;

struct WndMetadata {
	HWND hwnd;
	DWORD threadId;
	DWORD processId;
};

class GameWnd
{
public:
	bool isLoaded;
	bool isHooked;
	HANDLE handle;
	WndMetadata wndMetadata;
	Npc* prevChar;
	Npc* myChar;
	Npc* npcs;
	ConfigState* cfgState;
	GameWndManager* manager;

	GameWnd() {};
	GameWnd(GameWndManager* manager, WndMetadata wndMeta);
	DWORD GetCharBaseAddress();
	DWORD GetNpcsBaseAddress();
	void LoadCharData();
	void LoadNpcsData();
	void NotifyDeath();
};

