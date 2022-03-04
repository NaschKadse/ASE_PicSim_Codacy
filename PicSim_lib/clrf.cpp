#include "clrf.h"

void clrf::executeCMD(decodedCmdSimple ldecoded) {
    picDatalocal->setCycle(ramlocal->setRam(ldecoded.filepos, 0, picDatalocal->getCycle()));
    if (picSim::checkFilepos(ldecoded.filepos)) {
        picDatalocal->setProgramCounter(
                picSim::createPC(ramlocal->getRam(10).to_string(), ramlocal->getRam(2).to_string()));
    }
    ramlocal->zeroFlag(0);
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
    ramlocal->setRam(2, picSim::createPCL(picDatalocal->getProgramCounter().to_string()).to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 1);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
}