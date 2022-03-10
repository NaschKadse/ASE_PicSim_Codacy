#include "cmdgo.h"

void cmdgo::logic(decodedCmdSimple ldecoded) {
    utility utility1;
    utility1.setToBin(ldecoded.literal);
    utility1.setDigits(11);
    std::string BinaryString = utility1.toBinary();
    utility1.setToFill(BinaryString);
    inttobin = utility1.fillup();
}
void cmdgo::updateProgramCounter() {
    picDatalocal->setProgramCounter(stoi((pclath43(ramlocal->getRam(10).to_string()) + inttobin), 0, 2));

}
