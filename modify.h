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

void modify(HANDLE handle, list<AddressItem>& addressList, int index, int value, char isInfOverwrite);
bool writeToMemory(HANDLE hProcess, DWORD address, int value);
