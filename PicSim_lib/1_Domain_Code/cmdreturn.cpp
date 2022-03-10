#include "cmdreturn.h"

void cmdreturn::logic(const decodedCmdSimple ldecoded) {
}
void cmdreturn::updateProgramCounter() {
    picDatalocal->setProgramCounter(customStacklocal->top().to_ulong());
    customStacklocal->pop();
}
