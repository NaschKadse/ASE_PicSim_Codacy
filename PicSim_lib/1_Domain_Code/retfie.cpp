#include "retfie.h"

void retfie::executeCMD(const decodedCmdSimple ldecoded) {
    ramlocal->modifyBit(11, 7, true); // GIE zurücksetzen
    increasePC("stack");
    increaseCycle2();
    increaseRuntime2();
}