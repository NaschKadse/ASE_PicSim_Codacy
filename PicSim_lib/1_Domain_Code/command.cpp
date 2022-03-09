#include "command.h"

void command::increasePC() const {
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
    ramlocal->setRam(2, (int) createPCL(picDatalocal->getProgramCounter().to_string()).to_ulong());
}
void command::increaseCycle1() const {
    picDatalocal->setCycle(picDatalocal->getCycle() + 1);
}
void command::increaseCycle2() const {
    picDatalocal->setCycle(picDatalocal->getCycle() + 2);
}
void command::increaseRuntime() const {
    picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
}
BYTE command::createPCL(const std::string &PCstring) {
    std::string PCL = PCstring.substr(5, 8);
    BYTE PCLreturn = stoi(PCL, nullptr, 2);
    return PCLreturn;
}
bool command::checkFilepos(int filepos_m) {
    if (filepos_m == 2) {
        return true;
    }
    return false;
}
int command::createPC(const std::string filepos10, std::string filepos2) {
    std::string PCLATH = filepos10;
    std::string PCL = filepos2;
    std::string PCLATH40 = PCLATH.substr(3, 5);
    std::string PCstring = PCLATH40 + PCL;
    PC PCbits = std::stoi(PCstring, 0, 2);
    return PCbits.to_ulong();
}
std::string command::pclath43(std::string PCLATH) {
    std::string PCLATH43 = PCLATH.substr(0, 2);
    return PCLATH43;
}
void command::increasePC(std::string inttobin) const {
    if (inttobin == "stack") {
        picDatalocal->setProgramCounter(customStacklocal->top().to_ulong());
        customStacklocal->pop();
    } else {
        picDatalocal->setProgramCounter(stoi((pclath43(ramlocal->getRam(10).to_string()) + inttobin), 0, 2));
    }
    ramlocal->setRam(2, createPCL(picDatalocal->getProgramCounter().to_string()).to_ulong());
}
void command::increaseRuntime2() const {
    picDatalocal->setRuntime(picDatalocal->getRuntime() + (2 * picDatalocal->getMultiplier()));
}
