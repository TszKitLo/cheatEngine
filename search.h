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