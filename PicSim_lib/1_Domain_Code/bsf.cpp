#include "bsf.h"

void bsf::logic(decodedCmdSimple ldecoded) {
    ramlocal->modifyBit(ldecoded.filepos, ldecoded.literal, true);
    if (checkFilepos(ldecoded.filepos)) {
        picDatalocal->setProgramCounter(
                createPC(ramlocal->getRam(10).to_string(), ramlocal->getRam(2).to_string()));
    }
}
void bsf::updateProgramCounter() {
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
}
