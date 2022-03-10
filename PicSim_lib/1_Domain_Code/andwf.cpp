#include "andwf.h"

void andwf::logic(decodedCmdSimple ldecoded) {
    if (ldecoded.dBit == 0) {
        picDatalocal->setWreg(picDatalocal->getWreg() & ramlocal->getRam(ldecoded.filepos));
        ramlocal->zeroFlag(picDatalocal->getWreg().to_ulong());
    } else {
        picDatalocal->setCycle(ramlocal->setRam(ldecoded.filepos, (picDatalocal->getWreg().to_ulong() &
                                                                   ramlocal->getRam(ldecoded.filepos).to_ulong()),
                                                picDatalocal->getCycle()));
        if (checkFilepos(ldecoded.filepos)) {
            picDatalocal->setProgramCounter(
                    createPC(ramlocal->getRam(10).to_string(), ramlocal->getRam(2).to_string()));
        }
        ramlocal->zeroFlag(ramlocal->getRam(ldecoded.filepos).to_ulong());
    }
}
void andwf::updateProgramCounter() {
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
}
