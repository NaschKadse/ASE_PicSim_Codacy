#include "movlw.h"

void movlw::executeCMD(decodedCmdSimple ldecoded) {
    picDatalocal->setWreg(ldecoded.literal);
    increasePC();
    increaseCycle1();
    increaseRuntime();
}



