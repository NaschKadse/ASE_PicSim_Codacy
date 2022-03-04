#include "sublw.h"

void sublw::executeCMD(decodedCmdSimple ldecoded) {
    additionReturn additionret = ramlocal->doaddition(ldecoded.literal, (~picDatalocal->getWreg()).to_ulong() + 1);
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
    ramlocal->setRam(2, picSim::createPCL(picDatalocal->getProgramCounter().to_string()).to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 1);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
}