#include "../header/incf.h"

void incf::execute(const decode::decodedCmd &ldecoded) {
    if (ldecoded.dBit == 0) {
        picDatalocal->setWreg(ramlocal->getRam(ldecoded.filepos).to_ulong() + 1);
        ramlocal->zeroFlag(picDatalocal->getWreg().to_ulong());
    } else {
        picDatalocal->setCycle(ramlocal->setRam(ldecoded.filepos, (ramlocal->getRam(ldecoded.filepos).to_ulong() + 1),
                                                picDatalocal->getCycle()));
        createPC(ldecoded.filepos);
        ramlocal->zeroFlag(ramlocal->getRam(ldecoded.filepos).to_ulong());
    }
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
    ramlocal->setRam(2, createPCL().to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 1);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
}