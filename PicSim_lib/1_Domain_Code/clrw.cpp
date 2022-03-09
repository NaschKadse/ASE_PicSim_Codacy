#include "clrw.h"

void clrw::executeCMD(const decodedCmdSimple ldecoded) {
    picDatalocal->setWreg(0);
    ramlocal->zeroFlag(0);
    increasePC();
    increaseCycle1();
    increaseRuntime();
}