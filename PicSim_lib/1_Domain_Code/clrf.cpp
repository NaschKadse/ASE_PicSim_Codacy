#include "clrf.h"

void clrf::executeCMD(decodedCmdSimple ldecoded) {
    picDatalocal->setCycle(ramlocal->setRam(ldecoded.filepos, 0, picDatalocal->getCycle()));
    if (checkFilepos(ldecoded.filepos)) {
        picDatalocal->setProgramCounter(
                createPC(ramlocal->getRam(10).to_string(), ramlocal->getRam(2).to_string()));
    }
    ramlocal->zeroFlag(0);
    increasePC();
    increaseCycle1();
    increaseRuntime();
}