#include "../header/cmdcall.h"

void cmdcall::executeCMD(decodedCmdSimple ldecoded) {
    utility convert(ldecoded.literal);
    utility fillup(convert.toBinary(), 11);
    std::string inttobin = fillup.fillup();
    customStacklocal->push(picDatalocal->getProgramCounter().to_ulong() + 1);
    picDatalocal->setProgramCounter(stoi((picSim::pclath43(ramlocal->getRam(10).to_string()) + inttobin), 0, 2));
    ramlocal->setRam(2, picSim::createPCL(picDatalocal->getProgramCounter().to_string()).to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 2);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + (2 * picDatalocal->getMultiplier()));
}