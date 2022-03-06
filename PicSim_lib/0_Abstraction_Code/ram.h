#ifndef PICSIM2_0_RAM_H
#define PICSIM2_0_RAM_H

#include <bitset>
#include <iostream>
#include <string>
#include <cmath>
#include "0_Abstraction_Code/picData.h"

typedef std::bitset<1> BIT;
typedef std::bitset<8> BYTE;
struct addition {
    BIT sum = 0;
    BIT carry = 0;
};
struct additionReturn {
    BYTE result;
    int carry;
    int dcarry;
};

class ram {
public:
    void ramBitInputGui(int registerNo, int bit, bool set);
    void modifyBitGui(int filepos, int bit, bool set);
    void ramInput(std::string input, int buttonNumber);
    static ram *getRamObject();
    int setRam(int filepos_ram, int content_l, int cycle_l);
    void setRam(int filepos_ram, int content_l);
    BYTE getRam(int filepos_ram);
    BYTE getRamGui(int filepos_ram);
    std::string getBitGui(int registerNo, int bit);
    void print();
    void modifyBit(int filepos, int bit, bool set);
    void zeroFlag(int value);
    additionReturn doaddition(BYTE A, BYTE B);
    void setCarry(bool value);
    void setDCarry(bool value);
    int prescaler();
    void clearRam();
    void releaseInstance();
private:
    picData *picData1 = picData::getPicDataObject();
    BYTE ramArray[256];
    ram() {};
    ~ram() {};
    static ram *ramObject;
    addition halfAdder(BIT A, BIT B);
    addition Adder(BIT A, BIT B, BIT carry);
    int checkFilepos(int filepos_ram);
};

#endif //PICSIM2_0_RAM_H
