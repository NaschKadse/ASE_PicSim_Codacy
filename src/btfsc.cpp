#include "../header/btfsc.h"

void btfsc::execute(const decode::decodedCmd &ldecoded) {
    BYTE ramcontent = ramlocal->getRam(ldecoded.filepos);
    if (ramcontent.test(ldecoded.literal) == 0) {
        //NOP
        picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
        ramlocal->setRam(2, createPCL().to_ulong());
        picDatalocal->setCycle(picDatalocal->getCycle() + 1);
        picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
        // NOP ENDE
    }
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
    ramlocal->setRam(2, createPCL().to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 1);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
}