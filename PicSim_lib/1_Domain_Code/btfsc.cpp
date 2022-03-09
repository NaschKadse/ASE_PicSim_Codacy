#include "btfsc.h"

void btfsc::executeCMD(decodedCmdSimple ldecoded) {
    BYTE ramcontent = ramlocal->getRam(ldecoded.filepos);
    if (ramcontent.test(ldecoded.literal) == 0) {
        //NOP
        increasePC();
        increaseCycle1();
        increaseRuntime();
        // NOP ENDE
    }
    increasePC();
    increaseCycle1();
    increaseRuntime();
}