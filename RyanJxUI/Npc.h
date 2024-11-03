

#pragma once

#include <Windows.h>
#include <iostream>
#include <winuser.h>
#include <msclr/marshal_cppstd.h> // For string conversion


using namespace System;

class Npc
{
public:
	BYTE npc1[64];

	int isBoss;

	BYTE npc1A[4100];

	int curHp;  // 0x1048

	BYTE npc2[12];

	int curMp; // 0x1048

	BYTE npc3[689];

	char name[32]; // 0x130D

	BYTE npc3A[567];

	bool fightState; // 0x1564

	BYTE npc[65107];

public:
	static void ReadData(HANDLE hProc, DWORD npcAdd, Npc* npcBuffer);
	Npc();
	String^ getDisplayText();
};

