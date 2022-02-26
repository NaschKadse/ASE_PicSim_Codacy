#include "../header/cmdreturn.h"

void cmdreturn::executeCMD(const decodedCmdSimple ldecoded) {
    picDatalocal->setProgramCounter(customStacklocal->top().to_ulong());
    ramlocal->setRam(2, picSim::createPCL(picDatalocal->getProgramCounter().to_string()).to_ulong());
    customStacklocal->pop();
    picDatalocal->setCycle(picDatalocal->getCycle() + 2);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + (2 * picDatalocal->getMultiplier()));
}