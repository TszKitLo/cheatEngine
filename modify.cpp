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
#include "addressitem.h"
#include <iomanip>

using namespace std;

void modify(HANDLE handle, std::list<AddressItem>& addressList, int index, int value, char isInfOverwrite);
bool writeToMemory(HANDLE hProcess, DWORD address, int value);

void modify(HANDLE handle, std::list<AddressItem>& addressList, int index, int value, char isInfOverwrite) {

	std::list<AddressItem>::iterator it = addressList.begin();
	std::advance(it, index);

	writeToMemory(handle, (it->getAddress()), value);
	if (isInfOverwrite == 'y') {
		while (true) {
			writeToMemory(handle, (it->getAddress()), value);
		}
	}
}

bool writeToMemory(HANDLE hProcess, DWORD address, int value) {
	BOOL rpmReturn2 = WriteProcessMemory(hProcess, (LPVOID)address, &value, sizeof(value), 0);
	if (rpmReturn2 == FALSE) {
		printf("ReadProcessMemory failed \n");
		system("pause");
		return EXIT_FAILURE;
	}

	printf("The value updated to %d \n", value);
}
