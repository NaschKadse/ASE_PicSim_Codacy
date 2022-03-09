#include "btfss.h"

void btfss::executeCMD(decodedCmdSimple ldecoded) {
    BYTE ramcontent = ramlocal->getRam(ldecoded.filepos);
    if (ramcontent.test(ldecoded.literal) == 1) {
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