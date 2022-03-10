#include "command.h"

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
void command::executeCMD(decodedCmdSimple simpleDecodedStruct) {
    logic(simpleDecodedStruct);
    updateProgramCounter();
    updateProgramCounterRAM();
    updateCycle(simpleDecodedStruct.cmd);
    updateRuntime(simpleDecodedStruct.cmd);
}
void command::updateProgramCounterRAM() {
    ramlocal->setRam(2, (int) createPCL(picDatalocal->getProgramCounter().to_string()).to_ulong());
}
void command::updateCycle(std::string command) {
    if (command == "normal") {
        picDatalocal->setCycle(picDatalocal->getCycle() + 1);
    } else if (command == "double") {
        picDatalocal->setCycle(picDatalocal->getCycle() + 2);
    }
}
void command::updateRuntime(std::string command) {
    if (command == "normal") {
        picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
    } else if (command == "double") {
        picDatalocal->setRuntime(picDatalocal->getRuntime() + (2 * picDatalocal->getMultiplier()));
    }
}