#include "xorlw.h"

void xorlw::logic(decodedCmdSimple ldecoded) {
    picDatalocal->setWreg(picDatalocal->getWreg().to_ulong() ^ ldecoded.literal);
    ramlocal->zeroFlag(picDatalocal->getWreg().to_ulong());
}
void xorlw::updateProgramCounter() {
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
}
