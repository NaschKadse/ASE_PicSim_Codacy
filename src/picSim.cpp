#include "../header/picSim.h"


typedef std::bitset<8> BYTE;


void picSim::executecmd(decode::decodedCmd decoded) {


    if (decoded.cmd == "MOVLW") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.literal, thecommand);
        this->wreg = decoded.literal;
        programCounter = programCounter.to_ulong() + 1;
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle++;
        runtime = runtime + multiplier;
    }

    if (decoded.cmd == "RRF") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.filepos, thecommand);
        BYTE toshift = ram1.getRam(decoded.filepos);
        if (ram1.getRam(3).test(0) == 1) // Test Carry Ram
        {
            if (toshift.test(0) == 1) // test lsb = 1? --> carry
            {
                toshift >>= 1;
                toshift.set(7);
                ram1.setCarry(true);
                if (decoded.dBit == 0) {
                    wreg = toshift.to_ulong();
                } else {
                    cycle = ram1.setRam(decoded.filepos, toshift.to_ulong(), cycle);
                    createPC(decoded.filepos);
                }
            } else { // test lsb = 0 --> set no carry!
                toshift >>= 1;
                toshift.set(7);
                ram1.setCarry(false);
                if (decoded.dBit == 0) {
                    wreg = toshift.to_ulong();
                } else {
                    cycle = ram1.setRam(decoded.filepos, toshift.to_ulong(), cycle);
                    createPC(decoded.filepos);
                }
            }
        } else {// no carry before instruction!
            if (toshift.test(0) == 1) // test lsb = 1? --> carry
            {
                toshift >>= 1;
                ram1.setCarry(true);
                if (decoded.dBit == 0) {
                    wreg = toshift.to_ulong();
                } else {
                    cycle = ram1.setRam(decoded.filepos, toshift.to_ulong(), cycle);
                    createPC(decoded.filepos);
                }
            } else {// test lsb = 0 --> set no carry!
                toshift >>= 1;
                ram1.setCarry(false);
                if (decoded.dBit == 0) {
                    wreg = toshift.to_ulong();
                } else {

                    cycle = ram1.setRam(decoded.filepos, toshift.to_ulong(), cycle);
                    createPC(decoded.filepos);
                }
            }
        }
        programCounter = programCounter.to_ulong() + 1;
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle++;
        runtime = runtime + multiplier;
    }


    if (decoded.cmd == "RLF") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.filepos, thecommand);
        BYTE toshift = ram1.getRam(decoded.filepos);
        if (ram1.getRam(3).test(0) == 1) // Test Carry Ram
        {
            if (toshift.test(7) == 1) // test msb = 1? --> carry
            {
                toshift <<= 1;
                toshift.set(0);
                ram1.setCarry(true);
                if (decoded.dBit == 0) {
                    wreg = toshift.to_ulong();
                } else {

                    cycle = ram1.setRam(decoded.filepos, toshift.to_ulong(), cycle);
                    createPC(decoded.filepos);
                }
            } else { // test msb = 0 --> set no carry!
                toshift <<= 1;
                toshift.set(0);
                ram1.setCarry(false);
                if (decoded.dBit == 0) {
                    wreg = toshift.to_ulong();
                } else {
                    cycle = ram1.setRam(decoded.filepos, toshift.to_ulong(), cycle);
                    createPC(decoded.filepos);
                }
            }
        } else {// no carry before instruction!
            if (toshift.test(7) == 1) // test msb = 1? --> carry
            {
                toshift <<= 1;
                ram1.setCarry(true);
                if (decoded.dBit == 0) {
                    wreg = toshift.to_ulong();
                } else {

                    cycle = ram1.setRam(decoded.filepos, toshift.to_ulong(), cycle);
                    createPC(decoded.filepos);
                }
            } else { // test msb = 0 --> set no carry!
                toshift <<= 1;
                ram1.setCarry(false);
                if (decoded.dBit == 0) {
                    wreg = toshift.to_ulong();
                } else {
                    cycle = ram1.setRam(decoded.filepos, toshift.to_ulong(), cycle);
                    createPC(decoded.filepos);
                }
            }
        }
        programCounter = programCounter.to_ulong() + 1;
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle++;
        runtime = runtime + multiplier;
    }

    if (decoded.cmd == "ANDLW") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.literal, thecommand);
        wreg = wreg.to_ulong() & decoded.literal;
        ram1.zeroFlag(wreg.to_ulong());
        programCounter = programCounter.to_ulong() + 1;
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle++;
        runtime = runtime + multiplier;
    }

    if (decoded.cmd == "IORLW") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.literal, thecommand);
        wreg = wreg.to_ulong() | decoded.literal;
        ram1.zeroFlag(wreg.to_ulong());
        programCounter = programCounter.to_ulong() + 1;
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle++;
        runtime = runtime + multiplier;
    }

    if (decoded.cmd == "SUBLW") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.literal, thecommand);
        additionReturn additionret = ram1.doaddition(decoded.literal, (~wreg).to_ulong() + 1);
        wreg = additionret.result;
        ram1.zeroFlag(wreg.to_ulong());
        if (additionret.carry == 1) {
            ram1.setCarry(true);
        } else {
            ram1.setCarry(false);
        }
        if (additionret.dcarry == 1) {
            ram1.setDCarry(true);
        } else {
            ram1.setDCarry(false);
        }
        programCounter = programCounter.to_ulong() + 1;
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle++;
        runtime = runtime + multiplier;
    }

    if (decoded.cmd == "XORLW") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.literal, thecommand);
        wreg = wreg.to_ulong() ^ decoded.literal;
        ram1.zeroFlag(wreg.to_ulong());
        programCounter = programCounter.to_ulong() + 1;
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle++;
        runtime = runtime + multiplier;
    }
    if (decoded.cmd == "ADDLW") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.literal, thecommand);
        additionReturn additionret = ram1.doaddition(decoded.literal, wreg);
        wreg = additionret.result;
        ram1.zeroFlag(wreg.to_ulong());
        if (additionret.carry == 1) {
            ram1.setCarry(true);
        } else {
            ram1.setCarry(false);
        }
        if (additionret.dcarry == 1) {
            ram1.setDCarry(true);
        } else {
            ram1.setDCarry(false);
        }
        programCounter = programCounter.to_ulong() + 1;
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle++;
        runtime = runtime + multiplier;
    }

    if (decoded.cmd == "GOTO") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.literal, thecommand);
        utility convert(decoded.literal);
        utility fillup(convert.toBinary(), 11);
        std::string inttobin = fillup.fillup();
        programCounter = stoi((pclath43() + inttobin), 0, 2);
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle = cycle + 2;
        runtime = runtime + (2 * multiplier);
    }

    if (decoded.cmd == "CALL") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.literal, thecommand);
        utility convert(decoded.literal);
        utility fillup(convert.toBinary(), 11);
        std::string inttobin = fillup.fillup();
        stack1.push(programCounter.to_ulong() + 1);
        programCounter = stoi((pclath43() + inttobin), 0, 2);
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle = cycle + 2;
        runtime = runtime + (2 * multiplier);
    }

    if (decoded.cmd == "RETURN") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.literal, thecommand);
        programCounter = stack1.top().to_ulong();
        ram1.ramArray[2] = createPCL().to_ulong();
        stack1.pop();
        cycle = cycle + 2;
        runtime = runtime + (2 * multiplier);
    }

    if (decoded.cmd == "RETLW") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.literal, thecommand);
        wreg = decoded.literal;
        programCounter = stack1.top().to_ulong();
        ram1.ramArray[2] = createPCL().to_ulong();
        stack1.pop();
        cycle = cycle + 2;
        runtime = runtime + (2 * multiplier);
    }

    if (decoded.cmd == "NOP") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.literal, thecommand);
        nop();
    }

    if (decoded.cmd == "MOVWF") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.filepos, thecommand);
        cycle = ram1.setRam(decoded.filepos, wreg.to_ulong(), cycle);
        createPC(decoded.filepos);
        programCounter = programCounter.to_ulong() + 1;
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle++;
        runtime = runtime + multiplier;
    }

    if (decoded.cmd == "ADDWF") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.filepos, thecommand);
        if (decoded.dBit == 0) {
            additionReturn additionret = ram1.doaddition(ram1.getRam(decoded.filepos), wreg);
            wreg = additionret.result;
            ram1.zeroFlag(wreg.to_ulong());
            if (additionret.carry == 1) {
                ram1.setCarry(true);
            } else {
                ram1.setCarry(false);
            }
            if (additionret.dcarry == 1) {
                ram1.setDCarry(true);
            } else {
                ram1.setDCarry(false);
            }
        } else {
            additionReturn additionret = ram1.doaddition(ram1.getRam(decoded.filepos), wreg);
            cycle = ram1.setRam(decoded.filepos, additionret.result.to_ulong(), cycle);
            ram1.zeroFlag(ram1.getRam(decoded.filepos).to_ulong());
            if (additionret.carry == 1) {
                ram1.setCarry(true);
            } else {
                ram1.setCarry(false);
            }
            if (additionret.dcarry == 1) {
                ram1.setDCarry(true);
            } else {
                ram1.setDCarry(false);
            }
            createPC(decoded.filepos);
        }
        programCounter = programCounter.to_ulong() + 1;
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle++;
        runtime = runtime + multiplier;
    }

    if (decoded.cmd == "ANDWF") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.filepos, thecommand);
        if (decoded.dBit == 0) {
            wreg = wreg & ram1.getRam(decoded.filepos);
            ram1.zeroFlag(wreg.to_ulong());
        } else {
            cycle = ram1.setRam(decoded.filepos, (wreg.to_ulong() & ram1.getRam(decoded.filepos).to_ulong()), cycle);
            createPC(decoded.filepos);
            ram1.zeroFlag(ram1.getRam(decoded.filepos).to_ulong());
        }
        programCounter = programCounter.to_ulong() + 1;
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle++;
        runtime = runtime + multiplier;
    }

    if (decoded.cmd == "CLRF") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.filepos, thecommand);
        cycle = ram1.setRam(decoded.filepos, 0, cycle);
        createPC(decoded.filepos);
        ram1.zeroFlag(0);
        programCounter = programCounter.to_ulong() + 1;
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle++;
        runtime = runtime + multiplier;
    }

    if (decoded.cmd == "COMF") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.filepos, thecommand);
        BYTE ramcontent = ram1.getRam(decoded.filepos);
        if (decoded.dBit == 0) {
            wreg = ramcontent.flip();
            ram1.zeroFlag(wreg.to_ulong());
        } else {
            cycle = ram1.setRam(decoded.filepos, ramcontent.flip().to_ulong(), cycle);
            createPC(decoded.filepos);
            ram1.zeroFlag(ram1.getRam(decoded.filepos).to_ulong());
        }
        programCounter = programCounter.to_ulong() + 1;
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle++;
        runtime = runtime + multiplier;
    }

    if (decoded.cmd == "DECF") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.filepos, thecommand);
        if (decoded.dBit == 0) {
            wreg = ram1.getRam(decoded.filepos).to_ulong() - 1;
            ram1.zeroFlag(wreg.to_ulong());
        } else {
            cycle = ram1.setRam(decoded.filepos, (ram1.getRam(decoded.filepos).to_ulong() - 1), cycle);
            createPC(decoded.filepos);
            ram1.zeroFlag(ram1.getRam(decoded.filepos).to_ulong());
        }
        programCounter = programCounter.to_ulong() + 1;
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle++;
        runtime = runtime + multiplier;
    }

    if (decoded.cmd == "INCF") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.filepos, thecommand);
        if (decoded.dBit == 0) {
            wreg = ram1.getRam(decoded.filepos).to_ulong() + 1;
            ram1.zeroFlag(wreg.to_ulong());
        } else {
            cycle = ram1.setRam(decoded.filepos, (ram1.getRam(decoded.filepos).to_ulong() + 1), cycle);
            createPC(decoded.filepos);
            ram1.zeroFlag(ram1.getRam(decoded.filepos).to_ulong());
        }
        programCounter = programCounter.to_ulong() + 1;
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle++;
        runtime = runtime + multiplier;
    }

    if (decoded.cmd == "MOVF") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.filepos, thecommand);
        if (decoded.dBit == 0) {
            wreg = ram1.getRam(decoded.filepos);
            ram1.zeroFlag(wreg.to_ulong());
        } else {
            ram1.zeroFlag(ram1.getRam(decoded.filepos).to_ulong());
        }
        programCounter = programCounter.to_ulong() + 1;
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle++;
        runtime = runtime + multiplier;
    }

    if (decoded.cmd == "CLRW") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.filepos, thecommand);
        wreg = 0;
        ram1.zeroFlag(0);
        programCounter = programCounter.to_ulong() + 1;
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle++;
        runtime = runtime + multiplier;
    }

    if (decoded.cmd == "IORWF") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.filepos, thecommand);
        if (decoded.dBit == 0) {
            wreg = wreg.to_ulong() | ram1.getRam(decoded.filepos).to_ulong();
            ram1.zeroFlag(wreg.to_ulong());
        } else {
            cycle = ram1.setRam(decoded.filepos, wreg.to_ulong() | ram1.getRam(decoded.filepos).to_ulong(), cycle);
            createPC(decoded.filepos);
            ram1.zeroFlag(ram1.getRam(decoded.filepos).to_ulong());
        }
        programCounter = programCounter.to_ulong() + 1;
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle++;
        runtime = runtime + multiplier;
    }

    if (decoded.cmd == "XORWF") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.filepos, thecommand);
        if (decoded.dBit == 0) {
            wreg = wreg.to_ulong() ^ ram1.getRam(decoded.filepos).to_ulong();
            ram1.zeroFlag(wreg.to_ulong());
        } else {
            cycle = ram1.setRam(decoded.filepos, wreg.to_ulong() ^ ram1.getRam(decoded.filepos).to_ulong(), cycle);
            createPC(decoded.filepos);
            ram1.zeroFlag(ram1.getRam(decoded.filepos).to_ulong());
        }
        programCounter = programCounter.to_ulong() + 1;
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle++;
        runtime = runtime + multiplier;
    }

    if (decoded.cmd == "SUBWF") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.filepos, thecommand);
        if (decoded.dBit == 0) {
            additionReturn additionret = ram1.doaddition(ram1.getRam(decoded.filepos), (~wreg).to_ulong() + 1);
            wreg = additionret.result;
            ram1.zeroFlag(wreg.to_ulong());
            if (additionret.carry == 1) {
                ram1.setCarry(true);
            } else {
                ram1.setCarry(false);
            }
            if (additionret.dcarry == 1) {
                ram1.setDCarry(true);
            } else {
                ram1.setDCarry(false);
            }
        } else {
            additionReturn additionret = ram1.doaddition(ram1.getRam(decoded.filepos), (~wreg).to_ulong() + 1);
            cycle = ram1.setRam(decoded.filepos, additionret.result.to_ulong(), cycle);
            ram1.zeroFlag(ram1.getRam(decoded.filepos).to_ulong());
            if (additionret.carry == 1) {
                ram1.setCarry(true);
            } else {
                ram1.setCarry(false);
            }
            if (additionret.dcarry == 1) {
                ram1.setDCarry(true);
            } else {
                ram1.setDCarry(false);
            }
            createPC(decoded.filepos);
        }
        programCounter = programCounter.to_ulong() + 1;
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle++;
        runtime = runtime + multiplier;
    }

    if (decoded.cmd == "SWAPF") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.filepos, thecommand);
        std::string toswap = ram1.getRam(decoded.filepos).to_string();
        std::string lowerbyte = toswap.substr(4, 4);
        std::string highbyte = toswap.substr(0, 4);
        if (decoded.dBit == 0) {
            wreg = std::stoi((lowerbyte + highbyte), 0, 2);
        } else {
            cycle = ram1.setRam(decoded.filepos, std::stoi((lowerbyte + highbyte), 0, 2), cycle);
            createPC(decoded.filepos);
        }
        programCounter = programCounter.to_ulong() + 1;
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle++;
        runtime = runtime + multiplier;
    }

    if (decoded.cmd == "INCFSZ") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.filepos, thecommand);
        if (decoded.dBit == 0) {
            wreg = ram1.getRam(decoded.filepos).to_ulong() + 1;
            if (wreg == 0) {
                nop();
            }
        } else {
            cycle = ram1.setRam(decoded.filepos, ram1.getRam(decoded.filepos).to_ulong() + 1, cycle);
            createPC(decoded.filepos);
            if (ram1.getRam(decoded.filepos).to_ulong() == 0) {
                nop();
            }
        }
        programCounter = programCounter.to_ulong() + 1;
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle++;
        runtime = runtime + multiplier;
    }

    if (decoded.cmd == "DECFSZ") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.filepos, thecommand);
        if (decoded.dBit == 0) {
            wreg = ram1.getRam(decoded.filepos).to_ulong() - 1;
            if (wreg == 0) {
                nop();
            }
        } else {
            cycle = ram1.setRam(decoded.filepos, ram1.getRam(decoded.filepos).to_ulong() - 1, cycle);
            createPC(decoded.filepos);
            if (ram1.getRam(decoded.filepos).to_ulong() == 0) {
                nop();
            }
        }
        programCounter = programCounter.to_ulong() + 1;
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle++;
        runtime = runtime + multiplier;
    }

    if (decoded.cmd == "BSF") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.filepos, thecommand);
        ram1.modifyBit(decoded.filepos, decoded.literal, true);
        createPC(decoded.filepos);
        programCounter = programCounter.to_ulong() + 1;
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle++;
        runtime = runtime + multiplier;
    }

    if (decoded.cmd == "BCF") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.filepos, thecommand);
        ram1.modifyBit(decoded.filepos, decoded.literal, false);
        createPC(decoded.filepos);
        programCounter = programCounter.to_ulong() + 1;
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle++;
        runtime = runtime + multiplier;
    }

    if (decoded.cmd == "BTFSC") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.filepos, thecommand);
        BYTE ramcontent = ram1.getRam(decoded.filepos);
        if (ramcontent.test(decoded.literal) == 0) {
            nop();
        }
        programCounter = programCounter.to_ulong() + 1;
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle++;
        runtime = runtime + multiplier;
    }

    if (decoded.cmd == "BTFSS") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.filepos, thecommand);
        BYTE ramcontent = ram1.getRam(decoded.filepos);
        if (ramcontent.test(decoded.literal) == 1) {
            nop();
        }
        programCounter = programCounter.to_ulong() + 1;
        ram1.ramArray[2] = createPCL().to_ulong();
        cycle++;
        runtime = runtime + multiplier;
    }

    if (decoded.cmd == "RETFIE") {
        //utility::debugprint1(decoded.cmd, ram1.getRam(2), decoded.filepos, thecommand);
        ram1.modifyBit(11, 7, true); // GIE zurücksetzen
        programCounter = stack1.top().to_ulong();
        ram1.ramArray[2] = createPCL().to_ulong();
        stack1.pop();
        cycle = cycle + 2;
        runtime = runtime + (2 * multiplier);
    }
}


int picSim::run(std::string path, int guicounter) {
    inputfile file(path);
    file.readFile();
    thecommand = file.commandarray[guicounter];
    decode decode1(thecommand);
    if (ram1.ramArray[129].test(5) == 1) // Timer aus?
    {
        cycle = 0;
    }
    oldPrescale = ram1.prescaler();
    executecmd(decode1.decodeCommand());
    rb47interrupt();
    setoldrb47();
    newPrescale = ram1.prescaler();
    if (oldPrescale != newPrescale) {
        cycle = 1;
    }
    timer();
    edge = detectedge(oldedge, 0);
    rb0interrupt();

    // Console Debug
    /* ram1.print();
     std::printf("\nWREG %02lXh", wreg.to_ulong());
     std::printf(" | FSR %02lXh", ram1.getRam(4).to_ulong());
     std::printf(" | PCL %02lXh", ram1.getRam(2).to_ulong());
     std::printf(" | STATUS %02lXh", ram1.getRam(3).to_ulong());
     std::printf(" | PCLATH %02lXh\n\n", ram1.getRam(10).to_ulong());
     std::printf("Status-Register\n");
     std::printf("IRP %d", ram1.getRam(3).test(7));
     std::printf(" | RP1 %d", ram1.getRam(3).test(6));
     std::printf(" | RP0 %d", ram1.getRam(3).test(5));
     std::printf(" | TO %d", ram1.getRam(3).test(4));
     std::printf(" | PD %d", ram1.getRam(3).test(5));
     std::printf(" | Z %d", ram1.getRam(3).test(2));
     std::printf(" | DC %d", ram1.getRam(3).test(1));
     std::printf(" | C %d\n\n", ram1.getRam(3).test(0));
     std::printf("Option-Register\n");
     std::printf("RBP %d", ram1.ramArray[129].test(7));
     std::printf(" | IntEdg %d", ram1.ramArray[129].test(6));
     std::printf(" | TOCS %d", ram1.ramArray[129].test(5));
     std::printf(" | TOSE %d", ram1.ramArray[129].test(4));
     std::printf(" | PSA %d", ram1.ramArray[129].test(3));
     std::printf(" | PS2 %d", ram1.ramArray[129].test(2));
     std::printf(" | PS1 %d", ram1.ramArray[129].test(1));
     std::printf(" | PS0 %d\n\n", ram1.ramArray[129].test(0));
     std::printf("Andere-Register\n");
     std::printf("PC %04lXh", ram1.getRam(2).to_ulong());
     std::printf(" | Cycles %d", cycle);
     int printDebit = decode1.decodeCommand().dBit;
     if (printDebit != -1) {
         std::printf(" | DBIT %d", printDebit);
     }
     std::printf("\n\n");
     std::printf("Overwatch-Register\n");
     std::printf("TMR0 %02lXh ", ram1.ramArray[1].to_ulong());
     std::printf(" | Timer2 %02lXh ", ram1.ramArray[16].to_ulong());
     std::printf(" | Prescaler %d ", ram1.prescaler());
     std::printf(" | Laufzeit %.2f us \n\n", runtime);
     std::printf("Interrupt-Register\n");
     std::printf("GIE %d", ram1.ramArray[11].test(7));
     std::printf(" | EEIE %d", ram1.ramArray[11].test(6));
     std::printf(" | TOIE %d", ram1.ramArray[11].test(5));
     std::printf(" | INTE %d", ram1.ramArray[11].test(4));
     std::printf(" | RBIE %d", ram1.ramArray[11].test(3));
     std::printf(" | T0IF %d", ram1.ramArray[11].test(2));
     std::printf(" | INTF %d", ram1.ramArray[11].test(1));
     std::printf(" | RBIF %d\n\n", ram1.ramArray[11].test(0));
     std::printf("\n\n\n");*/

    return programCounter.to_ulong();
}

void picSim::nop() {
    programCounter = programCounter.to_ulong() + 1;
    ram1.ramArray[2] = createPCL().to_ulong();
    cycle++;
    runtime = runtime + multiplier;
}

void picSim::timer() {
    if (ram1.ramArray[129].test(5) == 0) {
        if (cycle >= ram1.prescaler()) {
            cycle = cycle - ram1.prescaler();
            ram1.ramArray[1] = ram1.ramArray[1].to_ulong() + 1;
            if (ram1.ramArray[1] == 0) {
                // Timer Interrupt
                if (ram1.ramArray[11].test(7) == 1) { // GIE erlaubt?
                    if (ram1.ramArray[11].test(5) == 1) { // T0IE is Timer Interrupt enabled?
                        ram1.modifyBit(11, 2, true); // set T0IF
                        ram1.modifyBit(11, 7, false); // GIE auf 0 ziehen um Interrupts zu sperren
                        stack1.push(programCounter.to_ulong()); // aktueller counter auf stack pushen
                        programCounter = 4; // 4 in PC
                    }
                }
            }
        }
    } else {
        // RA4 Timer
    }

}

void picSim::setoldrb47() {

    if (ram1.ramArray[6].test(4) == 1) {
        rb4 = true;
    } else {
        rb4 = false;
    }
    if (ram1.ramArray[6].test(5) == 1) {
        rb5 = true;
    } else {
        rb5 = false;
    }
    if (ram1.ramArray[6].test(6) == 1) {
        rb6 = true;
    } else {
        rb6 = false;
    }
    if (ram1.ramArray[6].test(7) == 1) {
        rb7 = true;
    } else {
        rb7 = false;
    }
}

void picSim::rb47interrupt() {
    if (ram1.ramArray[11].test(7) == 1) { // GIE erlaubt?
        if (ram1.ramArray[11].test(3) == 1) { // RBIE enabled??

            if (ram1.ramArray[134].test(7) == 1 && rb7 != ram1.ramArray[6].test(7)) {
                // Interrupt
                ram1.modifyBit(11, 7, false); // GIE auf 0 ziehen um Interrupts zu sperren
                ram1.modifyBit(11, 0, true); // RBIF set Interrupt aufgetreten?
                stack1.push(programCounter.to_ulong()); // aktueller counter auf stack pushen
                programCounter = 4; // 4 in PC
            }

            if (ram1.ramArray[134].test(6) == 1 && rb6 != ram1.ramArray[6].test(6)) {
                // Interrupt
                ram1.modifyBit(11, 7, false); // GIE auf 0 ziehen um Interrupts zu sperren
                ram1.modifyBit(11, 0, true); // RBIF set Interrupt aufgetreten?
                stack1.push(programCounter.to_ulong()); // aktueller counter auf stack pushen
                programCounter = 4; // 4 in PC
            }

            if (ram1.ramArray[134].test(5) == 1 && rb5 != ram1.ramArray[6].test(5)) {
                // Interrupt
                ram1.modifyBit(11, 7, false); // GIE auf 0 ziehen um Interrupts zu sperren
                ram1.modifyBit(11, 0, true); // RBIF set Interrupt aufgetreten?
                stack1.push(programCounter.to_ulong()); // aktueller counter auf stack pushen
                programCounter = 4; // 4 in PC
            }

            if (ram1.ramArray[134].test(4) == 1 && rb4 != ram1.ramArray[6].test(4)) {
                // Interrupt
                ram1.modifyBit(11, 7, false); // GIE auf 0 ziehen um Interrupts zu sperren
                ram1.modifyBit(11, 0, true); // RBIF set Interrupt aufgetreten?
                stack1.push(programCounter.to_ulong()); // aktueller counter auf stack pushen
                programCounter = 4; // 4 in PC
            }


        }
    }
}

void picSim::rb0interrupt() {
    if (ram1.ramArray[11].test(7) == 1) { // GIE erlaubt?
        if (ram1.ramArray[11].test(4) == 1) { // Interrupt RB0 enabled?
            if (ram1.ramArray[129].test(6)) {
                IntEdg = 1;
            } else {
                IntEdg = 0;
            }
            if (IntEdg == edge) { // interrupt?
                ram1.modifyBit(11, 1, true); // INTF set Interrupt aufgetreten?
                ram1.modifyBit(11, 7, false); // GIE auf 0 ziehen um Interrupts zu sperren
                stack1.push(programCounter.to_ulong()); // aktueller counter auf stack pushen
                programCounter = 4; // 4 in PC
            }
        }
    }
}

int picSim::detectedge(int oldvalue, int port) {

    int portvalue;
    if (ram1.ramArray[6].test(port)) {
        portvalue = 1;
    } else {
        portvalue = 0;
    }

    if (oldvalue == portvalue) {
        return 2;
    }


    if (oldvalue < portvalue) {
        this->oldedge = portvalue;
        return 1; // rising edge
    } else {
        this->oldedge = portvalue;
        return 0; // falling edge
    }
}

void picSim::init(bool type) {
    wreg = 0;
    cycle = ram1.setRam(2, 0, cycle);
    if (type) {
        ram1.modifyBit(3, 7, false);
        ram1.modifyBit(3, 6, false);
        ram1.modifyBit(3, 5, false);
        ram1.modifyBit(3, 4, true);
        ram1.modifyBit(3, 3, true);
        ram1.modifyBit(131, 7, false);
        ram1.modifyBit(131, 6, false);
        ram1.modifyBit(131, 5, false);
        ram1.modifyBit(131, 4, true);
        ram1.modifyBit(131, 3, true);
    } else {
        ram1.modifyBit(3, 7, false);
        ram1.modifyBit(3, 6, false);
        ram1.modifyBit(3, 5, false);
        ram1.modifyBit(131, 7, false);
        ram1.modifyBit(131, 6, false);
        ram1.modifyBit(131, 5, false);

    }
    cycle = ram1.setRam(10, 0, cycle);
    cycle = ram1.setRam(11, 0, cycle);
    cycle = ram1.setRam(129, 255, cycle);
    cycle = ram1.setRam(133, 255, cycle);
    cycle = ram1.setRam(134, 255, cycle);
    programCounter = 0;
}

int picSim::ping(int ramIndex) {
    return ram1.ramArray[ramIndex].to_ulong();
}

void picSim::ramInput(std::string input, int buttonNumber) {
    int i;
    i = std::stoi(input, 0, 16);
    cycle = ram1.setRam(buttonNumber, i, cycle);
}

void picSim::ramBitInput(int registerNo, int bit, bool set) {
    ram1.modifyBit(registerNo, bit, set);
}

std::string picSim::getBit(int registerNo, int bit) {
    std::string bitString;

    if (ram1.ramArray[registerNo].test(bit)) {
        bitString = "1";
    } else {
        bitString = "0";
    }
    return bitString;
}

int picSim::getRam(int filepos) {
    return ram1.ramArray[filepos].to_ulong();
}

BYTE picSim::getWreg() {
    return wreg;
}

void picSim::setWreg(std::string input) {
    int i;
    i = std::stoi(input, 0, 16);
    wreg = i;
}

int picSim::getPSA() {
    return newPrescale;
}

int picSim::getCycles() {
    return cycle;
}

float picSim::getRuntime() {
    return runtime;
}

void picSim::setMultiplier(float mult) {
    multiplier = mult;
}

float picSim::getMultiplier() {
    return multiplier;
}

void picSim::resetRuntime() {
    runtime = 0;
}


std::string picSim::showPCLATH() {
    std::string PCLATH8;
    std::string PCLATH5;
    std::string PCL;
    std::string PC;

    PCLATH8 = ram1.getRam(10).to_string();
    PCLATH5 = PCLATH8.substr(3, 5);
    PCL = ram1.getRam(2).to_string();
    PC = PCLATH5 + PCL;

    return PC;
}

std::string picSim::getPCLATH() {
    std::string PCLATH8;
    std::string PCLATH5;

    PCLATH8 = ram1.getRam(10).to_string();
    PCLATH5 = PCLATH8.substr(3, 5);

    return PCLATH5;
}

unsigned long picSim::getPC() {
    return programCounter.to_ulong();
}

void picSim::setPC() {
    programCounter = stoi((getPCLATH() + ram1.getRam(2).to_string()), 0, 2);
}

typedef std::bitset<13> PC;

PC picSim::getStack(int pos) {
    return stack1.getstack(pos);
}

void picSim::clearStack() {
    stack1.clearStack();
}

void picSim::clearRAM() {
    ram1.clearRam();
}

void picSim::createPC(int filepos_m) {
    if (filepos_m == 2) {
        std::string PCLATH = ram1.getRam(10).to_string();
        std::string PCL = ram1.getRam(2).to_string();
        std::string PCLATH40 = PCLATH.substr(3, 5);

        std::string PCstring = PCLATH40 + PCL;

        PC PCbits = std::stoi(PCstring, 0, 2);

        programCounter = PCbits.to_ulong();
    } else {
        programCounter = programCounter.to_ulong();
    }
}

BYTE picSim::createPCL() {
    std::string PCstring = programCounter.to_string();
    std::string PCL = PCstring.substr(5, 8);
    BYTE PCLreturn = stoi(PCL, 0, 2);
    return PCLreturn;
}

std::string picSim::pclath43() {
    std::string PCLATH = ram1.getRam(10).to_string();
    std::string PCLATH43 = PCLATH.substr(0, 2);
    return PCLATH43;
}

void picSim::reset() {
    cycle = 0;
    oldPrescale = 0;
    newPrescale = 0;
    oldedge = 0;
    runtime = 0;
    clearStack();
    resetRuntime();
}