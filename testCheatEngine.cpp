#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>

using namespace std;


void search(HANDLE handle, int target) {
	MEMORY_BASIC_INFORMATION info;
	unsigned char* p = NULL;
	
	cout << "searching value: " << target << "..." << endl;

	for (p = NULL;
		VirtualQueryEx(handle, p, &info, sizeof(info)) == sizeof(info);
		p += info.RegionSize)
	{
		if (info.State == MEM_COMMIT) {
			//cout << info.BaseAddress << "-" << info.RegionSize << " | " << info.Type << endl;
			 
			int value;
			for (int offset = 0; offset < (int)info.RegionSize; offset +=4) {
				
				DWORD targetAddr = (DWORD)((int)info.BaseAddress + offset);
				ReadProcessMemory(handle, (PBYTE*)targetAddr, &value, sizeof(value), 0);
	 
				if (value == target) {
					cout << (int)info.BaseAddress + offset << endl;
				}
			}
		}
	}

	DWORD targetAddr = (DWORD)(0x9a730);
	int value;
	ReadProcessMemory(handle, (PBYTE*)targetAddr, &value, sizeof(value), 0);

	cout << value;
}


int main() {
//	int n = 0x00400000 + 0x0017B0B8;
//	int* basePtr = &n; // 0x00400000 + 0x0017B0B8; // windows default base addr + ac.exe = base pointer
	
//	cout << "basePtr is " << hex << *basePtr << endl;
//	cout << "basePtr is " << hex << &basePtr << endl;
	
	int baseAddr = 0x007551E0; // base pointer point to
	int offset = 0x140; // ammo / money / whatever
	int writeAmount = 20; // amount we want to write


	cout << "Base Addr is " << hex << baseAddr << endl;
	cout << "Offset is " << hex << offset << endl;
	cout << "Target Addr is " << hex << baseAddr + offset << endl;

	DWORD targetAddr = (DWORD)(baseAddr + offset); // the amount address
	cout << "Target Addr (DWORD) is " << targetAddr << endl;

	HWND hwnd = FindWindowA(NULL, "AssaultCube"); // find the window title of the game

	cout << "Test" << endl;
	if (hwnd == NULL) {
		cout << "Cannot find the game" << endl;
		Sleep(3000); //wait for 3 seconds
		exit(-1);
	}
	else {
		DWORD processID; // store game process ID
		GetWindowThreadProcessId(hwnd, &processID); // get game process ID
		HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);

		if (processID == NULL) {
			cout << "Cannot obtain process" << endl;
			Sleep(3000);
			exit(-1);
		}
		else {
			// Create infinte loop to write value into address
			cout << "Hack begin" << endl;
			while (true) {
				WriteProcessMemory(handle, (PBYTE*)targetAddr, &writeAmount, sizeof(writeAmount), 0);
			}
		}
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file