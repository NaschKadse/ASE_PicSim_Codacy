#include "../header/movlw.h"

void movlw::execute(const decode::decodedCmd &ldecoded) {
    picDatalocal->setWreg(ldecoded.literal);
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
    ramlocal->setRam(2, createPCL().to_ulong());
    std::cout << "createpcl: " << createPCL().to_ulong() << "\n";
    picDatalocal->setCycle(picDatalocal->getCycle() + 1);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
}



