#include "../header/retlw.h"

void retlw::execute(const decode::decodedCmd &ldecoded) {
    picDatalocal->setWreg(ldecoded.literal);
picDatalocal->setProgramCounter(customStacklocal->top().to_ulong());

    ramlocal->setRam(2, createPCL().to_ulong());
    customStacklocal->pop();
    picDatalocal->setCycle(picDatalocal->getCycle() + 2);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + (2 * picDatalocal->getMultiplier()));
}