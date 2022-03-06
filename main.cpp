#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>
#include <list>
#include "search.h"
 
using namespace std;

int doNewSearch(HANDLE handle);

int main(int argc, char* argv[]) {


	char* winddowsName;
	if (argc != 3) {
		cout << "Usage: cheat_engine -n [Windows name]";
		return 0;
	}

	if (strcmp (argv[1] , "-n") == 0  ) {
		winddowsName = argv[2];
	}
	else {
		cout << "error: unknow switch: " << argv[0];
		exit(-1);
	}

	DWORD processID; // store game process ID
	HWND hwnd = FindWindowA(NULL, winddowsName); // find the window title of the game
	GetWindowThreadProcessId(hwnd, &processID); // get game process ID
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);

	cout << "Test" << endl;
	if (hwnd == NULL) {
		cout << "Cannot find the game" << endl;
		Sleep(3000); //wait for 3 seconds
		exit(-1);
	}

	cout << "Created the windows handle" << endl;

	char input = 0;

	while (input != 'x') {
		cout << "Menu: (n)New search, (m)Modify value, (x)Exit" << endl;
		cin >> input;
	
		switch (input) {
			case 'n':
				doNewSearch(handle);
				break;

			case 'm':
				cout << "not implemented yet ...";
				break;

			case 'x':
				exit(0);
				break;
		}
	}

	return 0;
	/*
	* modify value example..............
	* 
	* 
	
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

	if (processID == NULL) {
		cout << "Cannot obtain process" << endl;
		Sleep(3000);
		exit(-1);
	}
	else {
		//to test memory search:
		doSearch(handle);
			 
		// Create infinte loop to write value into address
		cout << "Hack begin" << endl;
		while (true) {
			WriteProcessMemory(handle, (PBYTE*)targetAddr, &writeAmount, sizeof(writeAmount), 0);
		}
	}
	*/
}

int doNewSearch(HANDLE handle) {
	//TODO: Make it as loop for continuously searching..

	list<int>* addressList = new list<int>;

	int value = 0;
	cout << "Enter your search value: ";
	cin >> value;
	cout << "searching: " << value << endl;
	newSearch(handle, value, *addressList);

	while (true) {
		cout << "Enter your search value: ";
		cin >> value;
		cout << "searching: " << value << endl;
		contSearch(handle, value, *addressList);
	}
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
