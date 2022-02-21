#include "../header/cmdcall.h"

void cmdcall::execute(const decode::decodedCmd &ldecoded) {
    utility convert(ldecoded.literal);
    utility fillup(convert.toBinary(), 11);
    std::string inttobin = fillup.fillup();
    customStacklocal->push(picDatalocal->getProgramCounter().to_ulong() + 1);
    picDatalocal->setProgramCounter(stoi((picSim::pclath43() + inttobin), 0, 2));
    ramlocal->setRam(2, createPCL().to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 2);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + (2 * picDatalocal->getMultiplier()));
}