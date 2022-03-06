#include "cmdgo.h"

void cmdgo::executeCMD(decodedCmdSimple ldecoded) {

    utility utility1;

    utility1.setToBin(ldecoded.literal);
    utility1.setDigits(11);
    std::string BinaryString = utility1.toBinary();
    utility1.setToFill(BinaryString);
    std::string inttobin = utility1.fillup();

    //utility convert(ldecoded.literal);
    //utility fillup(convert.toBinary(), 11);
    //std::string inttobin = fillup.fillup();
    picDatalocal->setProgramCounter(stoi((picSim::pclath43(ramlocal->getRam(10).to_string()) + inttobin), 0, 2));
    ramlocal->setRam(2, picSim::createPCL(picDatalocal->getProgramCounter().to_string()).to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 2);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + (2 * picDatalocal->getMultiplier()));
}