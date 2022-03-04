#include "decfsz.h"

void decfsz::executeCMD(decodedCmdSimple ldecoded) {
    if (ldecoded.dBit == 0) {
        picDatalocal->setWreg(ramlocal->getRam(ldecoded.filepos).to_ulong() - 1);
        if (picDatalocal->getWreg() == 0) {

            //NOP
            picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
            ramlocal->setRam(2, picSim::createPCL(picDatalocal->getProgramCounter().to_string()).to_ulong());
            picDatalocal->setCycle(picDatalocal->getCycle() + 1);
            picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
            // NOP ENDE
        }
    } else {
        picDatalocal->setCycle(ramlocal->setRam(ldecoded.filepos, ramlocal->getRam(ldecoded.filepos).to_ulong() - 1,
                                                picDatalocal->getCycle()));
        if (picSim::checkFilepos(ldecoded.filepos)) {
            picDatalocal->setProgramCounter(
                    picSim::createPC(ramlocal->getRam(10).to_string(), ramlocal->getRam(2).to_string()));
        }
        if (ramlocal->getRam(ldecoded.filepos).to_ulong() == 0) {
            //NOP
            picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
            ramlocal->setRam(2, picSim::createPCL(picDatalocal->getProgramCounter().to_string()).to_ulong());
            picDatalocal->setCycle(picDatalocal->getCycle() + 1);
            picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
            // NOP ENDE
        }
    }
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
    ramlocal->setRam(2, picSim::createPCL(picDatalocal->getProgramCounter().to_string()).to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 1);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
}