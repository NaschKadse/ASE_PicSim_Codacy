#include "../header/clrw.h"

void clrw::execute(const decode::decodedCmd &ldecoded) {
    picDatalocal->setWreg(0);
    ramlocal->zeroFlag(0);
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
    ramlocal->setRam(2, createPCL().to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 1);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
}