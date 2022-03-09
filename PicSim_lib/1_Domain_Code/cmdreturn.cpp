#include "cmdreturn.h"

void cmdreturn::executeCMD(const decodedCmdSimple ldecoded) {
    increasePC("stack");
    increaseCycle2();
    increaseRuntime2();
}