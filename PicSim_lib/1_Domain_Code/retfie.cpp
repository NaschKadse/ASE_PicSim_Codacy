#include "retfie.h"

void retfie::logic(const decodedCmdSimple ldecoded) {
    ramlocal->modifyBit(11, 7, true); // GIE zurücksetzen
}
void retfie::updateProgramCounter() {
    picDatalocal->setProgramCounter(customStacklocal->top().to_ulong());
    customStacklocal->pop();
}
