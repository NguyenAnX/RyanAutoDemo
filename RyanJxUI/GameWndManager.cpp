#include "GameWndManager.h"

std::vector<WndMetadata> wndMetadata;

BOOL CALLBACK enumWindowCallback(HWND hWnd, LPARAM lparam) {
	int length = GetWindowTextLength(hWnd);
	char* buffer = new char[length + 1];
	GetWindowTextA(hWnd, buffer, length + 1);
	std::string windowTitle(buffer);
	delete[] buffer;

	if (IsWindowVisible(hWnd) && length != 0 && (windowTitle == "Vo Lam Truyen Ky")) {
		DWORD processID;
		DWORD threadId = GetWindowThreadProcessId(hWnd, &processID);
		if (!threadId) return TRUE;
		wndMetadata.push_back({hWnd, threadId, processID});
	}
	return TRUE;
}

void getProcessWindowHandles()
{
	wndMetadata.clear();
	EnumWindows((WNDENUMPROC)enumWindowCallback, NULL);
}


GameWndManager::GameWndManager(RLogger* logger)
{
	this->logger = logger;
}

void GameWndManager::notifyDeath()
{
	for (auto wm : this->gameWnds) {
		wm.second->NotifyDeath();
	}
}

GameWnd* GameWndManager::getGameWnd(DWORD pid)
{
	if (this->gameWnds.find(pid) == this->gameWnds.end()) {
		return nullptr;
	}

	return this->gameWnds[pid];
}

GameWnd* GameWndManager::getGameWnd(System::String^ pid)
{	
	DWORD iPID;
	try {
		iPID = Convert::ToUInt32(pid);
		return this->getGameWnd(iPID);
	}
	catch (System::FormatException^) {
		return nullptr;
	}
}

void GameWndManager::RefreshGameData()
{
	getProcessWindowHandles();
	for (auto it = this->gameWnds.begin(); it != this->gameWnds.end();) {
		auto found = std::find_if(
			wndMetadata.begin(),
			wndMetadata.end(),
			[&](const WndMetadata& p) { return p.processId == it->first; }
		);
		if (found == wndMetadata.end()) {
			it = this->gameWnds.erase(it);
		}
		else {
			++it;
		}
	}

	for (const auto& meta : wndMetadata) {
		if (this->gameWnds.find(meta.processId) == this->gameWnds.end()) {
			GameWnd* gw = new GameWnd(this, meta);
			gw->LoadCharData();
			gw->LoadNpcsData();
			this->gameWnds[meta.processId] = gw;
		}
		else {
			GameWnd* gw = this->gameWnds[meta.processId];
			gw->LoadCharData();
			gw->LoadNpcsData();
		}
	}
}
