#include "xorlw.h"

void xorlw::executeCMD(decodedCmdSimple ldecoded) {
    picDatalocal->setWreg(picDatalocal->getWreg().to_ulong() ^ ldecoded.literal);
    ramlocal->zeroFlag(picDatalocal->getWreg().to_ulong());
    increasePC();
    increaseCycle1();
    increaseRuntime();
}