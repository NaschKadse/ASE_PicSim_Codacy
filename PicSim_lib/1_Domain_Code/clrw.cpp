#include "clrw.h"

void clrw::executeCMD(const decodedCmdSimple ldecoded) {
    picDatalocal->setWreg(0);
    ramlocal->zeroFlag(0);
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
    ramlocal->setRam(2, picSim::createPCL(picDatalocal->getProgramCounter().to_string()).to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 1);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
}