#include "decf.h"

void decf::logic(decodedCmdSimple ldecoded) {
    if (ldecoded.dBit == 0) {
        picDatalocal->setWreg(ramlocal->getRam(ldecoded.filepos).to_ulong() - 1);
        ramlocal->zeroFlag(picDatalocal->getWreg().to_ulong());
    } else {
        picDatalocal->setCycle(ramlocal->setRam(ldecoded.filepos, (ramlocal->getRam(ldecoded.filepos).to_ulong() - 1),
                                                picDatalocal->getCycle()));
        if (checkFilepos(ldecoded.filepos)) {
            picDatalocal->setProgramCounter(
                    createPC(ramlocal->getRam(10).to_string(), ramlocal->getRam(2).to_string()));
        }
        ramlocal->zeroFlag(ramlocal->getRam(ldecoded.filepos).to_ulong());
    }
}
void decf::updateProgramCounter() {
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);

}
