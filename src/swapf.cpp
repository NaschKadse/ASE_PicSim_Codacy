#include "../header/swapf.h"

void swapf::execute(const decode::decodedCmd &ldecoded) {
    std::string toswap = ramlocal->getRam(ldecoded.filepos).to_string();
    std::string lowerbyte = toswap.substr(4, 4);
    std::string highbyte = toswap.substr(0, 4);
    if (ldecoded.dBit == 0) {
        picDatalocal->setWreg(std::stoi((lowerbyte + highbyte), 0, 2));
    } else {
        picDatalocal->setCycle(
                ramlocal->setRam(ldecoded.filepos, std::stoi((lowerbyte + highbyte), 0, 2), picDatalocal->getCycle()));
        createPC(ldecoded.filepos);
    }
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
    ramlocal->setRam(2, createPCL().to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 1);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
}