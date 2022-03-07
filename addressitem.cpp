#include <iostream>
using namespace std;
#include "addressitem.h"

AddressItem::AddressItem(int addr, int val) {
    address = addr;
    lastValue = val;
}


void AddressItem::setAddress(int x ) {
    address = x;
}

void AddressItem::setLastValue(int x) {
    lastValue = x;
}

int AddressItem::getAddress() {
    return address;
}

int AddressItem::getLastValue() {
    return lastValue;
}
