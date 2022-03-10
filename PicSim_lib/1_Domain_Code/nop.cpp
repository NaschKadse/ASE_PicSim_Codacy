#include "nop.h"

void nop::logic(const decodedCmdSimple ldecoded) {
}
void nop::updateProgramCounter() {
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
}
