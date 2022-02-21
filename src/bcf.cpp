#include "../header/bcf.h"

void bcf::execute(const decode::decodedCmd &ldecoded) {
    ramlocal->modifyBit(ldecoded.filepos, ldecoded.literal, false);
    createPC(ldecoded.filepos);
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
    ramlocal->setRam(2, createPCL().to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 1);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
}