#include "swapf.h"

void swapf::logic(decodedCmdSimple ldecoded) {
    std::string toswap = ramlocal->getRam(ldecoded.filepos).to_string();
    std::string lowerbyte = toswap.substr(4, 4);
    std::string highbyte = toswap.substr(0, 4);
    if (ldecoded.dBit == 0) {
        picDatalocal->setWreg(std::stoi((lowerbyte + highbyte), 0, 2));
    } else {
        picDatalocal->setCycle(
                ramlocal->setRam(ldecoded.filepos, std::stoi((lowerbyte + highbyte), 0, 2), picDatalocal->getCycle()));
        if (checkFilepos(ldecoded.filepos)) {
            picDatalocal->setProgramCounter(
                    createPC(ramlocal->getRam(10).to_string(), ramlocal->getRam(2).to_string()));
        }
    }
}
void swapf::updateProgramCounter() {
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
}
