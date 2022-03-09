#include "decfsz.h"

void decfsz::executeCMD(decodedCmdSimple ldecoded) {
    if (ldecoded.dBit == 0) {
        picDatalocal->setWreg(ramlocal->getRam(ldecoded.filepos).to_ulong() - 1);
        if (picDatalocal->getWreg() == 0) {

            //NOP
            increasePC();
            increaseCycle1();
            increaseRuntime();
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
            increasePC();
            increaseCycle1();
            increaseRuntime();
            // NOP ENDE
        }
    }
    increasePC();
    increaseCycle1();
    increaseRuntime();
}