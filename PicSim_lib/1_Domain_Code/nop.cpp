#include "nop.h"

void nop::executeCMD(const decodedCmdSimple ldecoded) {
    increasePC();
    increaseCycle1();
    increaseRuntime();
}