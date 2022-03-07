#pragma once
using namespace std;

class AddressItem {
    int address, lastValue;
public:
    AddressItem(int, int);
    void setAddress(int);
    void setLastValue(int);
    int getAddress();
    int getLastValue();
};
