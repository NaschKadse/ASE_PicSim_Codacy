#include "../header/rrf.h"

void rrf::executeCMD(decodedCmdSimple ldecoded) {
    BYTE toshift = ramlocal->getRam(ldecoded.filepos);
    if (ramlocal->getRam(3).test(0) == 1) // Test Carry Ram
    {
        if (toshift.test(0) == 1) // test lsb = 1? --> carry
        {
            toshift >>= 1;
            toshift.set(7);
            ramlocal->setCarry(true);
            if (ldecoded.dBit == 0) {
                picDatalocal->setWreg(toshift.to_ulong());
            } else {
                picDatalocal->setCycle(
                        ramlocal->setRam(ldecoded.filepos, toshift.to_ulong(), picDatalocal->getCycle()));
                if (picSim::checkFilepos(ldecoded.filepos)) {
                    picDatalocal->setProgramCounter(
                            picSim::createPC(ramlocal->getRam(10).to_string(), ramlocal->getRam(2).to_string()));
                }
            }
        } else { // test lsb = 0 --> set no carry!
            toshift >>= 1;
            toshift.set(7);
            ramlocal->setCarry(false);
            if (ldecoded.dBit == 0) {
                picDatalocal->setWreg(toshift.to_ulong());
            } else {
                picDatalocal->setCycle(
                        ramlocal->setRam(ldecoded.filepos, toshift.to_ulong(), picDatalocal->getCycle()));
                if (picSim::checkFilepos(ldecoded.filepos)) {
                    picDatalocal->setProgramCounter(
                            picSim::createPC(ramlocal->getRam(10).to_string(), ramlocal->getRam(2).to_string()));
                }
            }
        }
    } else {// no carry before instruction!
        if (toshift.test(0) == 1) // test lsb = 1? --> carry
        {
            toshift >>= 1;
            ramlocal->setCarry(true);
            if (ldecoded.dBit == 0) {
                picDatalocal->setWreg(toshift.to_ulong());
            } else {
                picDatalocal->setCycle(
                        ramlocal->setRam(ldecoded.filepos, toshift.to_ulong(), picDatalocal->getCycle()));
                if (picSim::checkFilepos(ldecoded.filepos)) {
                    picDatalocal->setProgramCounter(
                            picSim::createPC(ramlocal->getRam(10).to_string(), ramlocal->getRam(2).to_string()));
                }
            }
        } else {// test lsb = 0 --> set no carry!
            toshift >>= 1;
            ramlocal->setCarry(false);
            if (ldecoded.dBit == 0) {
                picDatalocal->setWreg(toshift.to_ulong());
            } else {
                picDatalocal->setCycle(
                        ramlocal->setRam(ldecoded.filepos, toshift.to_ulong(), picDatalocal->getCycle()));
                if (picSim::checkFilepos(ldecoded.filepos)) {
                    picDatalocal->setProgramCounter(
                            picSim::createPC(ramlocal->getRam(10).to_string(), ramlocal->getRam(2).to_string()));
                }
            }
        }
    }
    picDatalocal->setProgramCounter(picDatalocal->getProgramCounter().to_ulong() + 1);
    ramlocal->setRam(2, picSim::createPCL(picDatalocal->getProgramCounter().to_string()).to_ulong());
    picDatalocal->setCycle(picDatalocal->getCycle() + 1);
    picDatalocal->setRuntime(picDatalocal->getRuntime() + picDatalocal->getMultiplier());
}