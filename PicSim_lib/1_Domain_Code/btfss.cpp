#include "btfss.h"

void btfss::logic(decodedCmdSimple ldecoded) {
    BYTE ramcontent = ramlocal->getRam(ldecoded.filepos);
    if (ramcontent.test(ldecoded.literal) == 1) {
        //NOP
        updateProgramCounter();
        updateCycle("normal");
        updateRuntime("normal");
        // NOP ENDE
    }
}
void btfss::updateProgramCounter() {
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
}
