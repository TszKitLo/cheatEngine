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

void newSearch(HANDLE handle, int target, std::list<AddressItem>& addressList) {

	MEMORY_BASIC_INFORMATION info;
	unsigned char* p = NULL;

	cout << "newSearch: searching value: " << target << "..." << endl;
	int itemCount = 0;
	int printDotPerItem = 10;
	int newLinePerItem = 1000;

	// clear list before every new search
	addressList.clear();

	for (p = NULL;
		VirtualQueryEx(handle, p, &info, sizeof(info)) == sizeof(info);
		p += info.RegionSize)
	{
		if (info.State == MEM_COMMIT && info.AllocationProtect == PAGE_READWRITE && info.Type == MEM_PRIVATE) {
			//cout << info.BaseAddress << "-" << info.RegionSize << " | " << info.Type << endl;

			int value;
			for (int offset = 0; offset < (int)info.RegionSize; offset += 4) {

				DWORD targetAddr = (DWORD)((int)info.BaseAddress + offset);
				ReadProcessMemory(handle, (PBYTE*)targetAddr, &value, sizeof(value), 0);

				if (value == target) {

					/***  Debug use:
					cout << (int)info.BaseAddress + offset;
					cout << " " << info.AllocationProtect;
					cout << " " << info.Type << endl;
					**/
					AddressItem* ai = new AddressItem((int)info.BaseAddress + offset, value);
					addressList.push_back(*ai);
				}
			}
		}

		if (itemCount % printDotPerItem == 0) {
			cout << ".";
		}

		/*
		* TODO: fix the bug
		if (itemCount % newLinePerItem == 0 && itemCount > 0) {
			cout << "(Found " << itemCount << " items)" << endl;
		}
		*/

		itemCount++;

	}
	cout << endl;

	cout << "newSearch: found " << addressList.size() << " items" << endl;
}

void contSearch(HANDLE handle, int target, list<AddressItem>& addressList) {

	cout << "contSearch: addressList contains " << addressList.size() << " items" << endl;

	int value;
	std::list<AddressItem>::iterator it = addressList.begin();
	while (it != addressList.end()) {
		ReadProcessMemory(handle, (PBYTE*)(it->getAddress()), &value, sizeof(value), 0);

		//Debug use:
		//cout << value << "-" << *it << endl;

		if (value != target) {
			it = addressList.erase(it);

		}
		else {
			it++;
		}
	}
	cout << "contSearch: found " << addressList.size() << " items" << endl;
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

		std::cout << "[" << std::setw(2) << index << "] ";
		std::cout << "0x" << std::setfill('0') << std::setw(10) << std::hex << it->getAddress();
		std::cout << std::dec << " Last value: " << it->getLastValue() << endl;
		it++;
		index++;
	}

	if (addressList.size() > itemToList) {
		std::cout << "(another " << addressList.size() - itemToList << " hidden result.)" << endl;
	}
}