#include "../header/movwf.h"

void movwf::executeCMD(decodedCmdSimple ldecoded) {
    picDatalocal->setCycle(
            ramlocal->setRam(ldecoded.filepos, picDatalocal->getWreg().to_ulong(), picDatalocal->getCycle()));
    if (picSim::checkFilepos(ldecoded.filepos)) {
        picDatalocal->setProgramCounter(
                picSim::createPC(ramlocal->getRam(10).to_string(), ramlocal->getRam(2).to_string()));
    }
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
    ramlocal->setRam(2, picSim::createPCL(picDatalocal->getProgramCounter().to_string()).to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 1);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
}