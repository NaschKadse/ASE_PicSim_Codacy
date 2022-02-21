#include "../header/xorlw.h"

void xorlw::execute(const decode::decodedCmd &ldecoded) {
    picDatalocal->setWreg(picDatalocal->getWreg().to_ulong() ^ ldecoded.literal);
    ramlocal->zeroFlag(picDatalocal->getWreg().to_ulong());
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
    ramlocal->setRam(2, createPCL().to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 1);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
}