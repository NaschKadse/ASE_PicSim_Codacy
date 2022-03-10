#include "btfsc.h"

void btfsc::logic(decodedCmdSimple ldecoded) {
    BYTE ramcontent = ramlocal->getRam(ldecoded.filepos);
    if (ramcontent.test(ldecoded.literal) == 0) {
        //NOP
        updateProgramCounter();
        updateCycle("normal");
        updateRuntime("normal");
        // NOP ENDE
    }
}
void btfsc::updateProgramCounter() {
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
}
