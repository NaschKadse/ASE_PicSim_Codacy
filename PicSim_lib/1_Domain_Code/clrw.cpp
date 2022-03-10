#include "clrw.h"

void clrw::logic(const decodedCmdSimple ldecoded) {
    picDatalocal->setWreg(0);
    ramlocal->zeroFlag(0);
}
void clrw::updateProgramCounter() {
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
}
