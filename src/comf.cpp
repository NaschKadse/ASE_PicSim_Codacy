#include "../header/comf.h"

void comf::execute(const decode::decodedCmd &ldecoded) {
    BYTE ramcontent = ramlocal->getRam(ldecoded.filepos);
    if (ldecoded.dBit == 0) {
        picDatalocal->setWreg(ramcontent.flip());
        ramlocal->zeroFlag(picDatalocal->getWreg().to_ulong());
    } else {
        picDatalocal->setCycle(
                ramlocal->setRam(ldecoded.filepos, ramcontent.flip().to_ulong(), picDatalocal->getCycle()));
        createPC(ldecoded.filepos);
        ramlocal->zeroFlag(ramlocal->getRam(ldecoded.filepos).to_ulong());
    }
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
    ramlocal->setRam(2, createPCL().to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 1);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
}