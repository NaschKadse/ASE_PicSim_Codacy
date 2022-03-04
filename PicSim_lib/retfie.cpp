#include "retfie.h"

void retfie::executeCMD(const decodedCmdSimple ldecoded) {
    ramlocal->modifyBit(11, 7, true); // GIE zurücksetzen
    picDatalocal->setProgramCounter(customStacklocal->top().to_ulong());
    ramlocal->setRam(2, picSim::createPCL(picDatalocal->getProgramCounter().to_string()).to_ulong());
    customStacklocal->pop();
    picDatalocal->setCycle(picDatalocal->getCycle() + 2);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + (2 * picDatalocal->getMultiplier()));
}