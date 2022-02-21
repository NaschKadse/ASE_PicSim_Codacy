#include "../header/bsf.h"

void bsf::execute(const decode::decodedCmd &ldecoded) {
    ramlocal->modifyBit(ldecoded.filepos, ldecoded.literal, true);
    createPC(ldecoded.filepos);
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
    ramlocal->setRam(2, createPCL().to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 1);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
}