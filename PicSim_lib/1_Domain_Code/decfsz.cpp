#include "decfsz.h"

void decfsz::logic(decodedCmdSimple ldecoded) {
    if (ldecoded.dBit == 0) {
        picDatalocal->setWreg(ramlocal->getRam(ldecoded.filepos).to_ulong() - 1);
        if (picDatalocal->getWreg() == 0) {

            //NOP
            updateProgramCounter();
            updateCycle("normal");
            updateRuntime("normal");
            // NOP ENDE
        }
    } else {
        picDatalocal->setCycle(ramlocal->setRam(ldecoded.filepos, ramlocal->getRam(ldecoded.filepos).to_ulong() - 1,
                                                picDatalocal->getCycle()));
        if (checkFilepos(ldecoded.filepos)) {
            picDatalocal->setProgramCounter(
                    createPC(ramlocal->getRam(10).to_string(), ramlocal->getRam(2).to_string()));
        }
        if (ramlocal->getRam(ldecoded.filepos).to_ulong() == 0) {
            //NOP
            updateProgramCounter();
            updateCycle("normal");
            updateRuntime("normal");
            // NOP ENDE
        }
    }
}
void decfsz::updateProgramCounter() {
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
}
