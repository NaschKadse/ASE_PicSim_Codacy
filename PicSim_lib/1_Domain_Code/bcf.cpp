#include "bcf.h"

void bcf::logic(decodedCmdSimple ldecoded) {
    ramlocal->modifyBit(ldecoded.filepos, ldecoded.literal, false);
    if (checkFilepos(ldecoded.filepos)) {
        picDatalocal->setProgramCounter(
                createPC(ramlocal->getRam(10).to_string(), ramlocal->getRam(2).to_string()));
    }
}
void bcf::updateProgramCounter() {
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
}
