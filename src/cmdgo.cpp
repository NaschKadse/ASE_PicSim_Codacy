#include "../header/cmdgo.h"

void cmdgo::execute(const decode::decodedCmd &ldecoded) {
    utility convert(ldecoded.literal);
    utility fillup(convert.toBinary(), 11);
    std::string inttobin = fillup.fillup();
    picDatalocal->setProgramCounter(stoi((pclath43() + inttobin), 0, 2));
    ramlocal->setRam(2, createPCL().to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 2);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + (2 * picDatalocal->getMultiplier()));
}