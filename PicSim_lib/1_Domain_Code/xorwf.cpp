#include "xorwf.h"

void xorwf::executeCMD(decodedCmdSimple ldecoded) {
    if (ldecoded.dBit == 0) {
        picDatalocal->setWreg(picDatalocal->getWreg().to_ulong() ^ ramlocal->getRam(ldecoded.filepos).to_ulong());
        ramlocal->zeroFlag(picDatalocal->getWreg().to_ulong());
    } else {
        picDatalocal->setCycle(ramlocal->setRam(ldecoded.filepos, picDatalocal->getWreg().to_ulong() ^
                                                                  ramlocal->getRam(ldecoded.filepos).to_ulong(),
                                                picDatalocal->getCycle()));
        if (checkFilepos(ldecoded.filepos)) {
            picDatalocal->setProgramCounter(
                    createPC(ramlocal->getRam(10).to_string(), ramlocal->getRam(2).to_string()));
        }
        ramlocal->zeroFlag(ramlocal->getRam(ldecoded.filepos).to_ulong());
    }
    increasePC();
    increaseCycle1();
    increaseRuntime();
}