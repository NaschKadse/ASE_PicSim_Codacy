#include "../header/addwf.h"

void addwf::execute(const decode::decodedCmd &ldecoded) {
    if (ldecoded.dBit == 0) {
        additionReturn additionret = ramlocal->doaddition(ramlocal->getRam(ldecoded.filepos), picDatalocal->getWreg());
        picDatalocal->setWreg(additionret.result);
        ramlocal->zeroFlag(picDatalocal->getWreg().to_ulong());
        if (additionret.carry == 1) {
            ramlocal->setCarry(true);
        } else {
            ramlocal->setCarry(false);
        }
        if (additionret.dcarry == 1) {
            ramlocal->setDCarry(true);
        } else {
            ramlocal->setDCarry(false);
        }
    } else {
        additionReturn additionret = ramlocal->doaddition(ramlocal->getRam(ldecoded.filepos), picDatalocal->getWreg());
        picDatalocal->setCycle(
                ramlocal->setRam(ldecoded.filepos, additionret.result.to_ulong(), picDatalocal->getCycle()));
        ramlocal->zeroFlag(ramlocal->getRam(ldecoded.filepos).to_ulong());
        if (additionret.carry == 1) {
            ramlocal->setCarry(true);
        } else {
            ramlocal->setCarry(false);
        }
        if (additionret.dcarry == 1) {
            ramlocal->setDCarry(true);
        } else {
            ramlocal->setDCarry(false);
        }
        createPC(ldecoded.filepos);
    }
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
    ramlocal->setRam(2, createPCL().to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 1);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
}