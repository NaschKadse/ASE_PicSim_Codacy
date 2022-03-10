#include "iorlw.h"

void iorlw::logic(decodedCmdSimple ldecoded) {
    picDatalocal->setWreg(picDatalocal->getWreg().to_ulong() | ldecoded.literal);
    ramlocal->zeroFlag(picDatalocal->getWreg().to_ulong());
}
void iorlw::updateProgramCounter() {
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
}
