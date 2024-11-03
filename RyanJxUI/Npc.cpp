#include "Npc.h"

void Npc::ReadData(HANDLE hProc, DWORD npcAdd, Npc* npcBuffer)
{
	ReadProcessMemory(hProc, (LPCVOID)npcAdd, (LPVOID)npcBuffer, sizeof(*npcBuffer), NULL);
}

Npc::Npc()
{
}

String^ Npc::getDisplayText()
{
	String^ npcName = msclr::interop::marshal_as<String^>(this->name);
	String^ curHp = Convert::ToString(this->curHp);
	String^ curMp = Convert::ToString(this->curMp);
	String^ fightState = Convert::ToString(this->fightState);

	return String::Format("{0} - {1} - {2} - {3}", npcName, curHp, curMp, fightState);
}
