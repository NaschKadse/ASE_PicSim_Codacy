#include "movwf.h"

void movwf::logic(decodedCmdSimple ldecoded) {
    picDatalocal->setCycle(
            ramlocal->setRam(ldecoded.filepos, picDatalocal->getWreg().to_ulong(), picDatalocal->getCycle()));
    if (checkFilepos(ldecoded.filepos)) {
        picDatalocal->setProgramCounter(
                createPC(ramlocal->getRam(10).to_string(), ramlocal->getRam(2).to_string()));
    }
}
void movwf::updateProgramCounter() {
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
}
