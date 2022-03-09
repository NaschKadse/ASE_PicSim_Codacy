#include "addlw.h"

void addlw::executeCMD(decodedCmdSimple ldecoded) {
    additionReturn additionret = ramlocal->doaddition(ldecoded.literal, picDatalocal->getWreg());
    picDatalocal->setWreg(additionret.result);
    ramlocal->zeroFlag((int)picDatalocal->getWreg().to_ulong());
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
    increasePC();
    increaseCycle1();
    increaseRuntime();
}