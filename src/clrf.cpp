#include "../header/clrf.h"

void clrf::execute(const decode::decodedCmd &ldecoded) {
    picDatalocal->setCycle(ramlocal->setRam(ldecoded.filepos, 0, picDatalocal->getCycle()));
    createPC(ldecoded.filepos);
    ramlocal->zeroFlag(0);
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
    ramlocal->setRam(2, createPCL().to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 1);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
}