#include "retlw.h"

void retlw::logic(decodedCmdSimple ldecoded) {
    picDatalocal->setWreg(ldecoded.literal);
}
void retlw::updateProgramCounter() {
    picDatalocal->setProgramCounter(customStacklocal->top().to_ulong());
    customStacklocal->pop();
}