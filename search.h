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

using namespace std;

void newSearch(HANDLE handle, int target, list<AddressItem>& addressList);
void contSearch(HANDLE handle, int target, list<AddressItem>& addressList);
void listAddress(HANDLE handle, list<AddressItem>& addressList);
DWORD findingFinalPointer(int Pointerdepth, HANDLE hProcess, DWORD offsets[], DWORD BaseAddress);
bool readFromMemory(HANDLE hProcess, DWORD address);

const int INCREASED = 1;
const int DECREASED = 2;

void newUnknownScan(HANDLE handle, list<AddressItem>& addressList);
void unknownScanChanged(HANDLE handle, list<AddressItem>& addressList, int mode);
