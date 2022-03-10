#include "addlw.h"

void addlw::logic(decodedCmdSimple ldecoded) {
    additionReturn additionret = ramlocal->doaddition(ldecoded.literal, picDatalocal->getWreg());
    picDatalocal->setWreg(additionret.result);
    ramlocal->zeroFlag((int) picDatalocal->getWreg().to_ulong());
    if (additionret.carry == 1) {
        ramlocal->setCarry(true);
    } else {
        ramlocal->setCarry(false);
    }
    if (additionret.dcarry == 1) {
        ramlocal->setDCarry(true);
    } else {
        ramlocal->setDCarry(false);
    }
}
void addlw::updateProgramCounter() {
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
}
