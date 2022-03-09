#include "comf.h"

void comf::executeCMD(decodedCmdSimple ldecoded) {
    BYTE ramcontent = ramlocal->getRam(ldecoded.filepos);
    if (ldecoded.dBit == 0) {
        picDatalocal->setWreg(ramcontent.flip());
        ramlocal->zeroFlag(picDatalocal->getWreg().to_ulong());
    } else {
        picDatalocal->setCycle(
                ramlocal->setRam(ldecoded.filepos, ramcontent.flip().to_ulong(), picDatalocal->getCycle()));
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