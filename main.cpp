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

using namespace std;

void doNewSearch(HANDLE handle, list<AddressItem>& addressList);
void doContSearch(HANDLE handle, list<AddressItem>& addressList);
void listAddress(HANDLE handle, list<AddressItem>& addressList);
void doModify(HANDLE handle, list<AddressItem>& addressList);

// functions declaration using pointer
DWORD findingProcessId();
DWORD findingFinalPointer(int Pointerdepth, HANDLE hProcess, DWORD offsets[], DWORD BaseAddress);
bool readFromMemory(HANDLE hProcess, DWORD address);
bool writeToMemory(HANDLE hProcess, DWORD address, int value);
void updateAmmo(HANDLE hProcess);
void updateHealthPoint(HANDLE hProcess);


//Global variable
std::string nameOfGame = "AssaultCube";

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

	char input = 0;
	char input1 = 0;
	char input2 = 0;

	while (input != 'x') {
		cout << "Menu: (p) Pointer menu, (m)Memory search menu, (x)Exit" << endl;
		cin >> input;
	
		switch (input) {

		case 'p':
			while (input1 != 'b') {
				cout << "Menu: (a)Update Ammo, (h)Update Health Point, (b)Back" << endl;
				cin >> input1;

				switch (input1) {

				case 'a':
					updateAmmo(handle);
					break;

				case 'h':
					updateHealthPoint(handle);
					break;

				}
			}
			break;

		case 'm':
			while (input2 != 'b') {
				cout << "Menu: (n)New search, (c)Continue search (m)Modify value, (l)List address, (b)Back" << endl;
				cin >> input2;

				switch (input2) {

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

void doModify(HANDLE handle, list<AddressItem>& addressList) {
	listAddress(handle, addressList);
	int index;
	int value;
	cout << "Enter index address you want to change:" << endl;
	cin >> index;
	cout << "Enter value" << endl;
	cin >> value;

	std::list<AddressItem>::iterator it = addressList.begin();
	std::advance(it, index);

	WriteProcessMemory(handle, (PBYTE*)(it->getAddress()), &value, sizeof(value), 0);
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

void listAddress(HANDLE handle, list<AddressItem>& addressList) {
	int itemToList = 20;

	if (addressList.size() == 0) {
		cout << "The list is empty, please start a new search" << endl;
		return;
	}

	std::list<AddressItem>::iterator it = addressList.begin();
	int index = 0; 
	while (it != addressList.end() && itemToList > index) {

		//update the lastValue
		int value;
		ReadProcessMemory(handle, (PBYTE*)(it->getAddress()), &value, sizeof(value), 0);
		it->setLastValue(value);

		std::cout << "["  << std::setw(2) << index << "] ";
		std::cout << "0x" << std::setfill('0') << std::setw(10)  << std::hex << it->getAddress();
		std::cout << std::dec << " Last value: " << it->getLastValue() << endl;
		it++;
		index++;
	}

	if (addressList.size() > itemToList) {
		std::cout << "(another " << addressList.size() - itemToList << " hidden result.)" << endl;
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



void updateAmmo(HANDLE hProcess)
{	
	int value = 0;
	// Ammo Value read and update
	DWORD finalPointer = findingFinalPointer(1, hProcess, AmmoOffsets, BaseAddress);
	//cout << "final pointer" << finalPointer;

	printf("Reading Ammo Value .... \n");
	readFromMemory(hProcess, finalPointer);

	cout << "Enter your desire ammo value:" ;
	cin >> value;

	printf("Updating Ammo Value .... \n");
	writeToMemory(hProcess, finalPointer, value);

	//printf("Reading Ammo Value .... \n");
	//readFromMemory(hProcess, finalPointer);

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

	//printf("Reading Health Point Value .... \n");
	//readFromMemory(hProcess, finalPointer);

	printf("\n\n");
	
}

//Find the final pointer address 
DWORD findingFinalPointer(int Pointerdepth, HANDLE hProcess, DWORD offsets[], DWORD BaseAddress)
{
	DWORD pointerAddress;
	DWORD tempPointer;

	for (int i = 0; i < Pointerdepth; i++)
	{
		if (i == 0)
		{
			ReadProcessMemory(hProcess, (LPCVOID)BaseAddress, &tempPointer, sizeof(tempPointer), 0);
			pointerAddress = tempPointer + offsets[i];
			//printf("The address of final address i=0 %p\n", pointerAddress);

		}
		else {
			ReadProcessMemory(hProcess, (LPCVOID)pointerAddress, &tempPointer, sizeof(tempPointer), 0);
			pointerAddress = tempPointer + offsets[i];
		}
		//printf("The value of i:%d \n",i);

	}
	return pointerAddress;
}


bool readFromMemory(HANDLE hProcess, DWORD address)
{
	int rAmmoValue = -1;
	BOOL rpmReturn2 = ReadProcessMemory(hProcess, (LPCVOID)address, &rAmmoValue, sizeof(rAmmoValue), 0);
	if (rpmReturn2 == FALSE) {
		cout << "ReadProcessMemory failed. GetLastError = " << dec << GetLastError() << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	printf("The value is equal to %d \n", rAmmoValue);

}

bool writeToMemory(HANDLE hProcess, DWORD address, int value)
{
	BOOL rpmReturn2 = WriteProcessMemory(hProcess, (LPVOID)address, &value, sizeof(value), 0);
	if (rpmReturn2 == FALSE) {
		cout << "ReadProcessMemory failed. GetLastError = " << dec << GetLastError() << endl;
		system("pause");
		return EXIT_FAILURE;
	}

	printf("The value updated to %d \n", value);
}
