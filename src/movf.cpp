#include "../header/movf.h"

void movf::execute(const decode::decodedCmd &ldecoded) {
    if (ldecoded.dBit == 0) {
        picDatalocal->setWreg(ramlocal->getRam(ldecoded.filepos));
        ramlocal->zeroFlag(picDatalocal->getWreg().to_ulong());
    } else {
        ramlocal->zeroFlag(ramlocal->getRam(ldecoded.filepos).to_ulong());
    }
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
    ramlocal->setRam(2, createPCL().to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 1);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
}