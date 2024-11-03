#include "MainForm.h"
#include <Windows.h>
#include "Npc.h"
#include <vector>
#include <unordered_map>
#include <msclr/marshal_cppstd.h> // For string conversion
#include <chrono>
#include "StrHelper.h"
#include "../RyanJxDLL/RyanJxDLL.h"

#pragma comment(lib, "user32.lib")


using namespace std;
using namespace std::chrono;

System::Void RyanJxUI::MainForm::MainForm_Load(System::Object^ sender, System::EventArgs^ e)
{
	this->logger = new RLogger();
	this->wndManager = new GameWndManager(this->logger);
	this->myTimer = gcnew System::Threading::Timer(gcnew TimerCallback(this, &MainForm::OnTimerTick), nullptr, 0, 1000); // 0 initial delay, 1000ms interval
	this->logger->writeLog("************************** App started **************************");
}

System::Void RyanJxUI::MainForm::OnTimerTick(Object^ state) {
	this->wndManager->RefreshGameData();
	this->updatePlayerListView();
	this->wndManager->notifyDeath();
}

System::Void RyanJxUI::MainForm::updatePlayerListView() {
	if (lvPlayers->InvokeRequired) {
		lvPlayers->Invoke(gcnew Action(this, &MainForm::updatePlayerListView));
		return;
	}

	lvPlayers->BeginUpdate();
	for (int i = lvPlayers->Items->Count - 1; i >= 0; i--) {
		auto item = lvPlayers->Items[i];
		String^ pIdStr = item->SubItems[4]->Text;

		if (this->wndManager->getGameWnd(pIdStr) == NULL) {
			lvPlayers->Items->RemoveAt(i);
		}
	}
	lvPlayers->EndUpdate();

	for (auto it : this->wndManager->gameWnds) {
		GameWnd* gw = it.second;
		String^ itemText = "VLTK";
		String^ processId = Convert::ToString((int)gw->wndMetadata.processId);
		String^ threadId = Convert::ToString((int)gw->wndMetadata.threadId);
		String^ hwnd = Convert::ToString((int)gw->wndMetadata.hwnd);

		int idx = lvPlayers->Items->IndexOfKey(processId);
		String^ pName = StrHelper::ToSysStr(gw->myChar->name);
		String^ pHP = Convert::ToString(gw->myChar->curHp);
		String^ pMP = Convert::ToString(gw->myChar->curMp);
		String^ pFight = Convert::ToString(gw->myChar->fightState);

		if (idx == -1) {
			ListViewItem^ item = gcnew ListViewItem();
			item->Name = processId;
			item->Text = pName;
			item->SubItems->Add(pHP);
			item->SubItems->Add(pMP);
			item->SubItems->Add(pFight);
			item->SubItems->Add(processId);
			item->SubItems->Add(threadId);
			item->SubItems->Add(hwnd);

			lvPlayers->Items->Add(item);
		}
		else {
			auto curItem = lvPlayers->Items[idx];
			curItem->Text = pName;
			curItem->SubItems[1]->Text = pHP;
			curItem->SubItems[2]->Text = pMP;
			curItem->SubItems[3]->Text = pFight;
		}
	}
}

System::Void RyanJxUI::MainForm::applyConfigState(ConfigState* cfgState)
{
	if (!cfgState) {
		return;
	}

	this->chboxNotifyDeath->Checked = cfgState->notifyDeath;
}

GameWnd* RyanJxUI::MainForm::selectedWnd()
{
	if (lvPlayers->SelectedItems->Count != 1) {
		return NULL;
	}
	auto item = lvPlayers->SelectedItems[0];
	auto pid = item->SubItems[4]->Text;

	return this->wndManager->getGameWnd(pid);
}

System::Void RyanJxUI::MainForm::chboxNotifyDeath_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	GameWnd* gw = this->selectedWnd();
	if (!gw) return;

	gw->cfgState->notifyDeath = this->chboxNotifyDeath->Checked;
}

System::Void RyanJxUI::MainForm::timer1_Tick(System::Object^ sender, System::EventArgs^ e)
{
}

System::Void RyanJxUI::MainForm::timer2_Tick(System::Object^ sender, System::EventArgs^ e)
{
	
}

System::Void RyanJxUI::MainForm::buttonTrySomething_Click(System::Object^ sender, System::EventArgs^ e)
{
	GameWnd* gw = this->selectedWnd();
	if (!gw || gw->isHooked == false) {
		MessageBox::Show("Lost connection to game window");
		return;
	}

	SendMessage(gw->wndMetadata.hwnd, WH_RYANJX, NULL, 1);
}

System::Void RyanJxUI::MainForm::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
	GameWnd* gw = this->selectedWnd();
	if (!gw || gw->isHooked == false) {
		MessageBox::Show("Lost connection to game window");
		return;
	}

	SendMessage(gw->wndMetadata.hwnd, WH_RYANJX, NULL, 2);
}


System::Void RyanJxUI::MainForm::lvPlayers_ItemChecked(System::Object^ sender, System::Windows::Forms::ItemCheckedEventArgs^ e)
{
	auto item = e->Item;
	auto pid = item->SubItems[4]->Text;

	GameWnd* gw = this->wndManager->getGameWnd(pid);
	if (!gw) {
		MessageBox::Show("Error!! GameWnd not found. PID=" + pid);
		return;
	}

	if (item->Checked && gw->isHooked == false) {
		
		InjectDll(gw->wndMetadata.hwnd, gw->wndMetadata.threadId);
		MessageBeep(MB_OK);
		gw->isHooked = true;
	}

	if (item->Checked == false && gw->isHooked == true) {
		MessageBeep(MB_OKCANCEL);
		UnmapDll(gw->wndMetadata.hwnd);
		gw->isHooked = false;
	}
}

System::Void RyanJxUI::MainForm::lvPlayers_ItemSelectionChanged(System::Object^ sender, System::Windows::Forms::ListViewItemSelectionChangedEventArgs^ e)
{
	auto item = e->Item;
	if (!item->Selected) return;

	GameWnd* gw = this->selectedWnd();
	if (!gw) return;

	this->applyConfigState(gw->cfgState);
}

