#include "ram.h"

ram *ram::ramObject = nullptr;
ram *ram::getRamObject() {
    if (ramObject == nullptr) {
        ramObject = new ram();
    }
    return ramObject;
}
int ram::setRam(int filepos_ram, int content_l, int cycle_l) {
    if (filepos_ram == 2 || filepos_ram == 3 || filepos_ram == 4 || filepos_ram == 10 || filepos_ram == 11) {
        this->ramArray[filepos_ram] = content_l;
        this->ramArray[filepos_ram + 128] = content_l;
    } else {
        if (this->ramArray[3].test(5) == 0) {
            this->ramArray[checkFilepos(filepos_ram)] = content_l;
        } else { //RP0 == 1
            this->ramArray[checkFilepos(filepos_ram) + 128] = content_l;
        }
    }
    if (filepos_ram == 1) {
        return 0;
    } else {
        return cycle_l;
    }
}
BYTE ram::getRam(int filepos_ram) {
    if (this->ramArray[3].test(5) == 0) {
        return this->ramArray[checkFilepos(filepos_ram)];
    } else { //RP0 == 1
        return this->ramArray[checkFilepos(filepos_ram) + 128];
    }
}
BYTE ram::getRamGui(int filepos_ram) {
    return this->ramArray[checkFilepos(filepos_ram)];
}
std::string ram::getBitGui(int registerNo, int bit) {
    std::string bitString;
    if (getRamGui(registerNo).test(bit)) {
        bitString = "1";
    } else {
        bitString = "0";
    }
    return bitString;
}
int ram::checkFilepos(int filepos_ram) {
    if (filepos_ram == 0) {
        return ramArray[4].to_ulong();
    }
    return filepos_ram;
}
void ram::print() {
    int x = 0;
    std::cout << "######################   RAM   #######################\n";
    std::cout << "#                                                    #\n";
    std::cout << "#          00   01   02   03   04   05   06   07     #\n";
    std::cout << "#                                                    #\n";
    for (int i = 0; i < 32; i++) {
        std::cout << "#        -----------------------------------------   #\n";
        std::printf("#   %02X   ", x);
        for (int j = 0; j < 8; j++) {
            std::printf("| %02lX ", this->ramArray[j + (8 * i)].to_ulong());
        }
        x = x + 8;
        std::cout << "|   #\n";
    }
    std::cout << "#        -----------------------------------------   #\n";
    std::cout << "#                                                    #\n";
    std::cout << "######################################################\n";
}
void ram::modifyBit(int filepos, int bit, bool set) {
    BYTE ramcontent = getRam(filepos);
    if (set) {
        ramcontent.set(bit);
        setRam(filepos, ramcontent.to_ulong(), 0);
    } else {
        ramcontent.reset(bit);
        setRam(filepos, ramcontent.to_ulong(), 0);
    }
}
void ram::zeroFlag(int value) {
    if (value == 0) {
        modifyBit(3, 2, true);
    } else {
        modifyBit(3, 2, false);
    }
}
void ram::setCarry(bool value) {
    if (value) {
        modifyBit(3, 0, true);
    } else {
        modifyBit(3, 0, false);
    }
}
void ram::setDCarry(bool value) {
    if (value) {
        modifyBit(3, 1, true);
    } else {
        modifyBit(3, 1, false);
    }
}
addition ram::halfAdder(const BIT A, BIT B) {
    addition halfAdder;
    halfAdder.sum = A ^ B;
    halfAdder.carry = A & B;
    return halfAdder;
}
addition ram::Adder(const BIT A, BIT B, BIT carry) {
    addition adder;
    BIT carry1;
    BIT carry2;
    BIT carry3 = carry;
    BIT sum1 = halfAdder(A, B).sum;
    carry1 = halfAdder(A, B).carry;
    carry2 = halfAdder(sum1, carry3).carry;
    adder.sum = halfAdder(carry3, sum1).sum;
    carry3 = carry1 | carry2;
    adder.carry = carry3;
    return adder;
}
additionReturn ram::doaddition(BYTE A, BYTE B) {
    additionReturn return1;
    BYTE result = 0;
    BIT sum;
    BIT carry = 0;
    int theCarry;
    int theDCarry;
    for (int i = 0; i < 8; i++) {
        addition output = Adder((int) A[i], (int) B[i], carry);
        carry = output.carry;
        sum = output.sum;
        result = result.to_ulong() + (sum.to_ulong() * (pow(2, i)));
        return1.result = result;
        if (i == 7) {
            theCarry = carry.to_ulong();
            return1.carry = theCarry;
        }
        if (i == 3) {
            theDCarry = carry.to_ulong();
            return1.dcarry = theDCarry;
        }
    }
    return return1;
}
int ram::prescaler() {
    int prescale;
    std::string ps = this->ramArray[129].to_string();
    int pszahl = std::stoi(ps.substr(5, 3), 0, 2);
    switch (pszahl) {
        case 0:
            prescale = 2;
            break;
        case 1:
            prescale = 4;
            break;
        case 2:
            prescale = 8;
            break;
        case 3:
            prescale = 16;
            break;
        case 4:
            prescale = 32;
            break;
        case 5:
            prescale = 64;
            break;
        case 6:
            prescale = 128;
            break;
        case 7:
            prescale = 256;
            break;
        default:
            return -1;
    }
    if (this->ramArray[129].test(3) == 0) {
        return prescale;
    } else {
        return prescale / 2;
    }
}
void ram::clearRam() {
    for (int i = 0; i < 256; i++) {
        ramArray[i] = 0;
    }
}
void ram::setRam(int filepos_ram, int content_l) {
    if (filepos_ram == 2 || filepos_ram == 3 || filepos_ram == 4 || filepos_ram == 10 || filepos_ram == 11) {
        this->ramArray[filepos_ram] = content_l;
        this->ramArray[filepos_ram + 128] = content_l;
    } else {
        if (this->ramArray[3].test(5) == 0) {
            this->ramArray[checkFilepos(filepos_ram)] = content_l;
        } else { //RP0 == 1
            this->ramArray[checkFilepos(filepos_ram) + 128] = content_l;
        }
    }
}
void ram::ramInput(std::string input, int buttonNumber) {
    int i;
    i = std::stoi(input, 0, 16);
    picData1->setCycle(setRam(buttonNumber, i, picData1->getCycle()));
}
void ram::ramBitInputGui(int registerNo, int bit, bool set) {
    modifyBitGui(registerNo, bit, set);
}
void ram::modifyBitGui(int filepos, int bit, bool set) {
    BYTE ramcontent = getRamGui(filepos);
    if (set) {
        ramcontent.set(bit);
        this->ramArray[filepos] = ramcontent.to_ulong();
        //setRam(filepos, ramcontent.to_ulong(), 0);
    } else {
        ramcontent.reset(bit);
        this->ramArray[filepos] = ramcontent.to_ulong();
        //setRam(filepos, ramcontent.to_ulong(), 0);
    }
}
void ram::releaseInstance() {
    if (nullptr != ramObject) {
        delete ramObject;
        ramObject = nullptr;
    }
}

