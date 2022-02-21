#include "../header/movwf.h"

void movwf::execute(const decode::decodedCmd &ldecoded) {
    picDatalocal->setCycle(
            ramlocal->setRam(ldecoded.filepos, picDatalocal->getWreg().to_ulong(), picDatalocal->getCycle()));
    createPC(ldecoded.filepos);
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
    ramlocal->setRam(2, createPCL().to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 1);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
}