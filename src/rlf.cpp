#include "../header/rlf.h"

void rlf::execute(const decode::decodedCmd &ldecoded) {
    BYTE toshift = ramlocal->getRam(ldecoded.filepos);
    if (ramlocal->getRam(3).test(0) == 1) // Test Carry Ram
    {
        if (toshift.test(7) == 1) // test msb = 1? --> carry
        {
            toshift <<= 1;
            toshift.set(0);
            ramlocal->setCarry(true);
            if (ldecoded.dBit == 0) {
                picDatalocal->setWreg(toshift.to_ulong());
            } else {
                picDatalocal->setCycle(
                        ramlocal->setRam(ldecoded.filepos, toshift.to_ulong(), picDatalocal->getCycle()));
                createPC(ldecoded.filepos);
            }
        } else { // test msb = 0 --> set no carry!
            toshift <<= 1;
            toshift.set(0);
            ramlocal->setCarry(false);
            if (ldecoded.dBit == 0) {
                picDatalocal->setWreg(toshift.to_ulong());
            } else {
                picDatalocal->setCycle(
                        ramlocal->setRam(ldecoded.filepos, toshift.to_ulong(), picDatalocal->getCycle()));
                createPC(ldecoded.filepos);
            }
        }
    } else {// no carry before instruction!
        if (toshift.test(7) == 1) // test msb = 1? --> carry
        {
            toshift <<= 1;
            ramlocal->setCarry(true);
            if (ldecoded.dBit == 0) {
                picDatalocal->setWreg(toshift.to_ulong());
            } else {
                picDatalocal->setCycle(
                        ramlocal->setRam(ldecoded.filepos, toshift.to_ulong(), picDatalocal->getCycle()));
                createPC(ldecoded.filepos);
            }
        } else { // test msb = 0 --> set no carry!
            toshift <<= 1;
            ramlocal->setCarry(false);
            if (ldecoded.dBit == 0) {
                picDatalocal->setWreg(toshift.to_ulong());
            } else {
                picDatalocal->setCycle(
                        ramlocal->setRam(ldecoded.filepos, toshift.to_ulong(), picDatalocal->getCycle()));
                createPC(ldecoded.filepos);
            }
        }
    }
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
    ramlocal->setRam(2, createPCL().to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 1);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
}