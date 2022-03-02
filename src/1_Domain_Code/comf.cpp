#include "../../header/comf.h"

void comf::executeCMD(decodedCmdSimple ldecoded) {
    BYTE ramcontent = ramlocal->getRam(ldecoded.filepos);
    if (ldecoded.dBit == 0) {
        picDatalocal->setWreg(ramcontent.flip());
        ramlocal->zeroFlag(picDatalocal->getWreg().to_ulong());
    } else {
        picDatalocal->setCycle(
                ramlocal->setRam(ldecoded.filepos, ramcontent.flip().to_ulong(), picDatalocal->getCycle()));
        if (picSim::checkFilepos(ldecoded.filepos)) {
            picDatalocal->setProgramCounter(
                    picSim::createPC(ramlocal->getRam(10).to_string(), ramlocal->getRam(2).to_string()));
        }
        ramlocal->zeroFlag(ramlocal->getRam(ldecoded.filepos).to_ulong());
    }
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
    ramlocal->setRam(2, picSim::createPCL(picDatalocal->getProgramCounter().to_string()).to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 1);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
}