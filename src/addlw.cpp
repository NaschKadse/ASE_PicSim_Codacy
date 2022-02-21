#include "../header/addlw.h"

void addlw::execute(const decode::decodedCmd &ldecoded) {
    additionReturn additionret = ramlocal->doaddition(ldecoded.literal, picDatalocal->getWreg());
    picDatalocal->setWreg(additionret.result);
    ramlocal->zeroFlag(picDatalocal->getWreg().to_ulong());
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
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
    ramlocal->setRam(2, createPCL().to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 1);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
}