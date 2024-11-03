#include "GameWnd.h"
#include <chrono>

using namespace System;
using namespace std::chrono;

GameWnd::GameWnd(GameWndManager* manager, WndMetadata wndMeta)
{
	this->manager = manager;
	this->wndMetadata = wndMeta;
	this->handle = OpenProcess(PROCESS_ALL_ACCESS, false, this->wndMetadata.processId);
	this->isLoaded = false;
	this->isHooked = false;
	this->cfgState = new ConfigState();
	this->npcs = new Npc[NPC_NUM];
	this->prevChar = new Npc();
	this->myChar = new Npc();
}

DWORD GameWnd::GetCharBaseAddress()
{
	DWORD npcBaseAddress;
	ReadProcessMemory(this->handle, (LPCVOID)NPC_BASE, (LPVOID)&npcBaseAddress, 4, NULL);

	DWORD playerIndexBaseAddress;
	ReadProcessMemory(this->handle, (LPCVOID)PLAYER_INDEX_BASE, (LPVOID)&playerIndexBaseAddress, 4, NULL);

	DWORD playerIndexAddress = playerIndexBaseAddress + PLAYER_INDEX_OFFSET;
	DWORD playerIndex;
	ReadProcessMemory(this->handle, (LPCVOID)playerIndexAddress, (LPVOID)&playerIndex, 4, NULL);

	DWORD playerAddress = npcBaseAddress + playerIndex * NPC_SIZE;

	return playerAddress;
}

DWORD GameWnd::GetNpcsBaseAddress()
{
	DWORD npcBaseAddress;
	ReadProcessMemory(this->handle, (LPCVOID)NPC_BASE, (LPVOID)&npcBaseAddress, 4, NULL);

	DWORD playerIndexBaseAddress;
	ReadProcessMemory(this->handle, (LPCVOID)PLAYER_INDEX_BASE, (LPVOID)&playerIndexBaseAddress, 4, NULL);

	DWORD playerIndexAddress = playerIndexBaseAddress + PLAYER_INDEX_OFFSET;
	DWORD playerIndex;
	ReadProcessMemory(this->handle, (LPCVOID)playerIndexAddress, (LPVOID)&playerIndex, 4, NULL);

	return npcBaseAddress;
}

void GameWnd::LoadCharData()
{
	memcpy(this->prevChar, this->myChar, sizeof(*this->myChar));
	Npc::ReadData(this->handle, GetCharBaseAddress(), this->myChar);
	this->isLoaded = true;
}

void GameWnd::LoadNpcsData()
{
	int npcAdd = this->GetNpcsBaseAddress() + NPC_SIZE;

	for (int i = 1; i <= NPC_NUM - 1; i++) {
		Npc::ReadData(this->handle, npcAdd, &this->npcs[i]);
		npcAdd += NPC_SIZE;
	}
}

void GameWnd::NotifyDeath()
{
	Npc* prevNpc = this->prevChar;
	Npc* curNpc = this->myChar;

	if (!prevNpc || !curNpc) {
		return;
	}

	std::string npcName = std::string(curNpc->name);
	if (!this->cfgState->notifyDeath) {
		return;
	}

	if (prevNpc->fightState == 1 && curNpc->fightState == 0) {
		std::string msg = npcName + " back to the city";
		this->manager->logger->writeLog(msg);
	}
}

