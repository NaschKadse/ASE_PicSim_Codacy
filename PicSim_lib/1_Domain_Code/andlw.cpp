#include "andlw.h"

void andlw::logic(decodedCmdSimple ldecoded) {
    picDatalocal->setWreg(picDatalocal->getWreg().to_ulong() & ldecoded.literal);
    ramlocal->zeroFlag(picDatalocal->getWreg().to_ulong());
}
void andlw::updateProgramCounter() {
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
}
