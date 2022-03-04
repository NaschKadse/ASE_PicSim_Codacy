#include "btfss.h"

void btfss::executeCMD(decodedCmdSimple ldecoded) {
    BYTE ramcontent = ramlocal->getRam(ldecoded.filepos);
    if (ramcontent.test(ldecoded.literal) == 1) {
        //NOP
        picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
        ramlocal->setRam(2, picSim::createPCL(picDatalocal->getProgramCounter().to_string()).to_ulong());
        picDatalocal->setCycle(picDatalocal->getCycle() + 1);
        picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
        // NOP ENDE
    }
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
    ramlocal->setRam(2, picSim::createPCL(picDatalocal->getProgramCounter().to_string()).to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 1);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
}