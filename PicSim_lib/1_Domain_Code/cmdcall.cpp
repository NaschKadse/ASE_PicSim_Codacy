#include "cmdcall.h"

void cmdcall::logic(decodedCmdSimple ldecoded) {
    utility utility1;
    utility1.setToBin(ldecoded.literal);
    utility1.setDigits(11);
    std::string BinaryString = utility1.toBinary();
    utility1.setToFill(BinaryString);
    inttobin = utility1.fillup();
    customStacklocal->push(picDatalocal->getProgramCounter().to_ulong() + 1);
}
void cmdcall::updateProgramCounter() {
    picDatalocal->setProgramCounter(stoi((pclath43(ramlocal->getRam(10).to_string()) + inttobin), 0, 2));
}
