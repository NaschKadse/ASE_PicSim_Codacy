#include "cmdgo.h"

void cmdgo::executeCMD(decodedCmdSimple ldecoded) {
    utility utility1;
    utility1.setToBin(ldecoded.literal);
    utility1.setDigits(11);
    std::string BinaryString = utility1.toBinary();
    utility1.setToFill(BinaryString);
    std::string inttobin = utility1.fillup();
    increasePC(inttobin);
    increaseCycle2();
    increaseRuntime2();
}