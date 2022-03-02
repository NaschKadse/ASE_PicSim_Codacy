#include <string>
#include "../../header/picData.h"

picData *picData::picDataObject = nullptr;
picData *picData::getPicDataObject() {
    if (picDataObject == nullptr) {
        picDataObject = new picData();
    }
    return picDataObject;
}
void picData::setWreg(const BYTE lwreg) {
    this->wreg = lwreg;
}
BYTE picData::getWreg() {
    return this->wreg;
}
void picData::setProgramCounter(const PC lprogrammCounter) {
    this->programmCounter = lprogrammCounter;
}
PC picData::getProgramCounter() {
    return this->programmCounter;
}
void picData::setCycle(int lcycle) {
    this->cycle = lcycle;
}
int picData::getCycle() {
    return this->cycle;
}
void picData::setRuntime(float lruntime) {
    this->runtime = lruntime;
}
float picData::getRuntime() {
    return this->runtime;
}
void picData::setMultiplier(float lmultiplier) {
    this->multiplier = lmultiplier;
}
float picData::getMultiplier() {
    return this->multiplier;
}
void picData::setCommandArray(int pos, std::string larray) {
    commandarray[pos] = larray;
}
std::string picData::getCommandArray(int pos) {
    return commandarray[pos];
}

