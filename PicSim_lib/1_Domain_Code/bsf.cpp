#include "bsf.h"

void bsf::executeCMD(decodedCmdSimple ldecoded) {
    ramlocal->modifyBit(ldecoded.filepos, ldecoded.literal, true);
    if (checkFilepos(ldecoded.filepos)) {
        picDatalocal->setProgramCounter(
                createPC(ramlocal->getRam(10).to_string(), ramlocal->getRam(2).to_string()));
    }
    increasePC();
    increaseCycle1();
    increaseRuntime();
}