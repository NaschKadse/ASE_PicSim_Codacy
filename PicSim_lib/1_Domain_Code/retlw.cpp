#include "retlw.h"

void retlw::executeCMD(decodedCmdSimple ldecoded) {
    picDatalocal->setWreg(ldecoded.literal);
    increasePC("stack");
    increaseCycle2();
    increaseRuntime2();
}