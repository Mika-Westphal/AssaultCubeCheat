#include <iostream>
#include <windows.h>
#include "pointer.h"

HANDLE hProcess = NULL;

bool keyDownF1 = false;
bool keyDownF2 = false;
bool keyDownF3 = false;
bool keyDownF4 = false;

bool moduleOne = false;
bool moduleTwo = false;
bool moduleThree = false;
bool moduleFour = false;

BOOL IsElevated() {
	BOOL fRet = FALSE;
	HANDLE hToken = NULL;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
		TOKEN_ELEVATION Elevation;
		DWORD cbSize = sizeof(TOKEN_ELEVATION);
		if (GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize)) {
			fRet = Elevation.TokenIsElevated;
		}
	}
	if (hToken) {
		CloseHandle(hToken);
	}
	return fRet;
}

bool writeInt(int newValue, int address, HANDLE hProcess) {
	DWORD newdatasize = sizeof(newValue);
	if (WriteProcessMemory(hProcess, (LPVOID)address, &newValue, newdatasize, NULL)) {
		return true;
	}
	return false;
}

int readInt(int address, HANDLE hProcess) {
	int result = 0;
	if (ReadProcessMemory(hProcess, (LPVOID)address, &result, sizeof(result), NULL)) {
		return result;
	}

	return -1;
}

const char* readString(int address, HANDLE hProcess) {
	const char* result = "";
	if (ReadProcessMemory(hProcess, (LPVOID)address, &result, sizeof(result), NULL)) {
		return result;
	}
	return NULL;
}

HANDLE initProcess() {
	HWND hWnd = FindWindow(0, "AssaultCube");
	if (hWnd == 0) {
		return false;
	}

	DWORD process_ID;
	GetWindowThreadProcessId(hWnd, &process_ID);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_ID);
	if (!hProcess) {
		MessageBox(NULL, "Could not open the process!", "404 Skill not found!", MB_OK | MB_ICONERROR);
		return false;
	}
	return hProcess;
}

void updateKeyboard() {
	if (GetKeyState(VK_F1) < 0) {
		if (!keyDownF1) {
			moduleOne = !moduleOne;
		}
		keyDownF1 = true;
	}
	else {
		keyDownF1 = false;
	}

	if (GetKeyState(VK_F2) < 0) {
		if (!keyDownF2) {
			moduleTwo = !moduleTwo;
		}
		keyDownF2 = true;
	}
	else {
		keyDownF2 = false;
	}

	if (GetKeyState(VK_F3) < 0) {
		if (!keyDownF3) {
			moduleThree = !moduleThree;
		}
		keyDownF3 = true;
	}
	else {
		keyDownF3 = false;
	}

	if (GetKeyState(VK_F4) < 0) {
		if (!keyDownF4) {
			moduleFour = !moduleFour;
		}
		keyDownF4 = true;
	}
	else {
		keyDownF4 = false;
	}
}

void update() {
	updateKeyboard();

	if (moduleOne) {
		int address = p_base + o_health;
		int currentHealth = readInt(address, hProcess);
		if (currentHealth < 90) {
			writeInt(100, address, hProcess);
		}
	}

	if (moduleThree) {
		int address = p_base + o_speed;
		int currentSpeed = readInt(address, hProcess);
		if (currentSpeed == 10) {
			if (!writeInt(1, address, hProcess)) {
				MessageBox(NULL, "Failed to write at: " + address, "Excuse me WTF!", 0x00000010L);
				ExitProcess(EXIT_FAILURE);
			}			
		}
		else {
			
		}
	}
}

bool initCheat() {
	hProcess = initProcess();
	
	while (true) {
		update();
	}

}

int main() {
	if (!IsElevated()) {
		MessageBox(NULL, "You need to run the application as an administrator in order to use this cheat!", "Excuse me WTF!", 0x00000010L);
		ExitProcess(EXIT_FAILURE);
	}
	if (initCheat()) {
		ExitProcess(EXIT_SUCCESS);
	} else {
		ExitProcess(EXIT_FAILURE);
	}	
}