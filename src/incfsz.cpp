#include "../header/incfsz.h"

void incfsz::execute(const decode::decodedCmd &ldecoded) {
    if (ldecoded.dBit == 0) {
        picDatalocal->setWreg(ramlocal->getRam(ldecoded.filepos).to_ulong() + 1);
        if (picDatalocal->getWreg() == 0) {

            //NOP
            picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
            ramlocal->setRam(2, createPCL().to_ulong());
            picDatalocal->setCycle(picDatalocal->getCycle() + 1);
            picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
            // NOP ENDE
        }
    } else {
        picDatalocal->setCycle(ramlocal->setRam(ldecoded.filepos, ramlocal->getRam(ldecoded.filepos).to_ulong() + 1,
                                                picDatalocal->getCycle()));
        createPC(ldecoded.filepos);
        if (ramlocal->getRam(ldecoded.filepos).to_ulong() == 0) {

            //NOP
            picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
            ramlocal->setRam(2, createPCL().to_ulong());
            picDatalocal->setCycle(picDatalocal->getCycle() + 1);
            picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
            // NOP ENDE
        }
    }
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
    ramlocal->setRam(2, createPCL().to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 1);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
}