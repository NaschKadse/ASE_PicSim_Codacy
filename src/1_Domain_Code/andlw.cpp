#include "../../header/andlw.h"

void andlw::executeCMD(decodedCmdSimple ldecoded) {
    picDatalocal->setWreg(picDatalocal->getWreg().to_ulong() & ldecoded.literal);
    ramlocal->zeroFlag(picDatalocal->getWreg().to_ulong());
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
    ramlocal->setRam(2, picSim::createPCL(picDatalocal->getProgramCounter().to_string()).to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 1);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
}