#include "movlw.h"

void movlw::logic(decodedCmdSimple ldecoded) {
    picDatalocal->setWreg(ldecoded.literal);
}
void movlw::updateProgramCounter() {
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
}
