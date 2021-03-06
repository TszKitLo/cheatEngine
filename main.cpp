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
#include  <iomanip>
#include "addressitem.h"
#include "modify.h"

using namespace std;

void doNewSearch(HANDLE handle, list<AddressItem>& addressList);
void doContSearch(HANDLE handle, list<AddressItem>& addressList);
void doModify(HANDLE handle, list<AddressItem>& addressList);

void updateAmmo(HANDLE hProcess);
void updateHealthPoint(HANDLE hProcess);


//Global variable
// Ammo based address, offsets, target value
DWORD BaseAddress = { 0x0057B0B8 }; //  playerBaseAddress
//DWORD baseAddress = 0x0;
DWORD AmmoOffsets[] = { 0x140, 0x0 };
DWORD healthPointOffsets[] = { 0xEC, 0x0 };




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
		cout << "error: unknown switch: " << argv[0];
		exit(-1);
	}

	DWORD processID; // store game process ID
	HWND hwnd = FindWindowA(NULL, winddowsName); // find the window title of the game
	GetWindowThreadProcessId(hwnd, &processID); // get game process ID
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);

	if (hwnd == NULL) {
		cout << "Cannot find the game" << endl;
		Sleep(3000); //wait for 3 seconds
		exit(-1);
	}

	cout << "Created the windows handle" << endl;

	list<AddressItem>* addressList = new list<AddressItem>;

	char menuInput = 0;
	char pointerMenuInput = 0;
	char memorySearchInput = 0;

	while (menuInput != 'x') {
		cout << "Menu: (p) Pointer menu, (m)Memory search menu, (u)Unknown value scan (x)Exit" << endl;
		cin >> menuInput;
	
  		switch (menuInput) {

		case 'p':
			while (pointerMenuInput != 'b') {
				cout << "Menu: (a)Update Ammo, (h)Update Health Point, (b)Back" << endl;
				cin >> pointerMenuInput;

				switch (pointerMenuInput) {

				case 'a':
					updateAmmo(handle);
					break;

				case 'h':
					updateHealthPoint(handle);
					break;

				}
			}

			pointerMenuInput = '\0';  //clear 'b' key when go back to main menu
			break;

		case 'm':
			while (memorySearchInput != 'b') {
				cout << "Menu: (n)New search, (c)Continue search, (m)Modify value, (l)List address, (b)Back" << endl;
				cin >> memorySearchInput;

				switch (memorySearchInput) {

				case 'n':
					doNewSearch(handle, *addressList);
					listAddress(handle, *addressList);
					break;

				case 'c':
					doContSearch(handle, *addressList);
					listAddress(handle, *addressList);
					break;

				case 'm':
					doModify(handle, *addressList);
					break;

				case 'l':
					listAddress(handle, *addressList);
					break;

				}
			}

			memorySearchInput = '\0';	//clear 'b' key when go back to main menu
			break;

		case 'u':
			while (memorySearchInput != 'b') {
				cout << "Unknown value scan: (n)New scan, (+)Scan for increased value, (-)Scan for decreased value, (m)Modify value, (l)List address, (b)Back" << endl;
				cin >> memorySearchInput;

				switch (memorySearchInput) {

				case 'n':
					newUnknownScan(handle, *addressList);
					listAddress(handle, *addressList);
					break;

				case '+':
					unknownScanChanged(handle, *addressList, INCREASED);
					listAddress(handle, *addressList);
					break;

				case '-':
					unknownScanChanged(handle, *addressList, DECREASED);
					break;

				case 'm':
					doModify(handle, *addressList);
					break;

				case 'l':
					listAddress(handle, *addressList);
					break;

				}
			}

			memorySearchInput = '\0';	//clear 'b' key when go back to main menu
			break;


		case 'x':
			exit(0);
			break;
		}
	}

	return 0;
}

void doModify(HANDLE handle, list<AddressItem>& addressList) {
	listAddress(handle, addressList);
	int index;
	int value;
	char isInfOverwrite = 'n';
	cout << "Enter index address you want to change:" << endl;
	cin >> index;
	cout << "Enter value" << endl;
	cin >> value;
	cout << "Infinite overwrite? (y/n)" << endl;
	cin >> isInfOverwrite;

	modify(handle, addressList, index, value, isInfOverwrite);
}

void doNewSearch(HANDLE handle, list<AddressItem> & addressList) {
	int value = 0;
	cout << "Enter your search value: ";
	cin >> value;
	newSearch(handle, value, addressList);
}

void doContSearch(HANDLE handle, list<AddressItem>& addressList) {
	int value = 0;

	if (addressList.size() == 0) {
		return; 
	}

	cout << "Enter the value for next search: ";
	cin >> value;
	cout << "searching: " << value << endl;
	contSearch(handle, value, addressList);
	 
}


void updateAmmo(HANDLE hProcess)
{	
	int value = 0;
	// Ammo Value read and update
	DWORD finalPointer = findingFinalPointer(1, hProcess, AmmoOffsets, BaseAddress);

	printf("Reading Ammo Value .... \n");
	readFromMemory(hProcess, finalPointer);

	cout << "Enter your desire ammo value:" ;
	cin >> value;

	printf("Updating Ammo Value .... \n");
	writeToMemory(hProcess, finalPointer, value);

	printf("\n\n");
	
}


void updateHealthPoint(HANDLE hProcess)
{
	int value = 0;
	DWORD finalPointer = findingFinalPointer(1, hProcess, healthPointOffsets, BaseAddress);
	printf("Reading Health Point Value .... \n");
	readFromMemory(hProcess, finalPointer);

	cout << "Enter your desire health point:";
	cin >> value;

	printf("Updating Health Point Value .... \n");
	writeToMemory(hProcess, finalPointer, value);

	printf("\n\n");
	
}