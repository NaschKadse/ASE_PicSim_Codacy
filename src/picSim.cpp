#include "../header/picSim.h"
#include "../header/movlw.h"
#include "../header/rrf.h"
#include "../header/rlf.h"
#include "../header/andlw.h"
#include "../header/iorlw.h"
#include "../header/sublw.h"
#include "../header/xorlw.h"
#include "../header/addlw.h"
#include "../header/cmdgo.h"
#include "../header/cmdcall.h"
#include "../header/cmdreturn.h"
#include "../header/retlw.h"
#include "../header/retfie.h"
#include "../header/nop.h"
#include "../header/movwf.h"
#include "../header/addwf.h"
#include "../header/andwf.h"
#include "../header/clrf.h"
#include "../header/comf.h"
#include "../header/decf.h"
#include "../header/incf.h"
#include "../header/movf.h"
#include "../header/clrw.h"
#include "../header/iorwf.h"
#include "../header/xorwf.h"
#include "../header/subwf.h"
#include "../header/swapf.h"
#include "../header/incfsz.h"
#include "../header/decfsz.h"
#include "../header/bsf.h"
#include "../header/bcf.h"
#include "../header/btfsc.h"
#include "../header/btfss.h"

void picSim::executecmd(decode::decodedCmd decoded) {
    if (decoded.cmd == "MOVLW") {
        movlw *movlwexecute = new movlw(decoded);
        delete movlwexecute;
    }
    if (decoded.cmd == "RRF") {
        rrf *rrfexecute = new rrf(decoded);
        delete rrfexecute;
    }
    if (decoded.cmd == "RLF") {
        rlf *rlfexecute = new rlf(decoded);
        delete rlfexecute;
    }
    if (decoded.cmd == "ANDLW") {
        andlw *andlwexecute = new andlw(decoded);
        delete andlwexecute;
    }
    if (decoded.cmd == "IORLW") {
        iorlw *iorlwexecute = new iorlw(decoded);
        delete iorlwexecute;
    }
    if (decoded.cmd == "SUBLW") {
        sublw *sublwexecute = new sublw(decoded);
        delete sublwexecute;
    }
    if (decoded.cmd == "XORLW") {
        xorlw *xorlwexecute = new xorlw(decoded);
        delete xorlwexecute;
    }
    if (decoded.cmd == "ADDLW") {
        addlw *addlwexecute = new addlw(decoded);
        delete addlwexecute;
    }
    if (decoded.cmd == "GOTO") {
        cmdgo *cmdgoexecute = new cmdgo(decoded);
        delete cmdgoexecute;
    }
    if (decoded.cmd == "CALL") {
        cmdcall *cmdcallexecute = new cmdcall(decoded);
        delete cmdcallexecute;
    }
    if (decoded.cmd == "RETURN") {
        cmdreturn *cmdreturnexecute = new cmdreturn(decoded);
        delete cmdreturnexecute;
    }
    if (decoded.cmd == "RETLW") {
        retlw *retlwexecute = new retlw(decoded);
        delete retlwexecute;
    }
    if (decoded.cmd == "NOP") {
        class nop *nopexecute = new class nop(decoded);
        delete nopexecute;
    }
    if (decoded.cmd == "MOVWF") {
        movwf *movwfexecute = new movwf(decoded);
        delete movwfexecute;
    }
    if (decoded.cmd == "ADDWF") {
        addwf *addwfexecute = new addwf(decoded);
        delete addwfexecute;
    }
    if (decoded.cmd == "ANDWF") {
        andwf *andwfexecute = new andwf(decoded);
        delete andwfexecute;
    }
    if (decoded.cmd == "CLRF") {
        clrf *clrfexecute = new clrf(decoded);
        delete clrfexecute;
    }
    if (decoded.cmd == "COMF") {
        comf *comfexecute = new comf(decoded);
        delete comfexecute;
    }
    if (decoded.cmd == "DECF") {
        decf *decfexecute = new decf(decoded);
        delete decfexecute;
    }
    if (decoded.cmd == "INCF") {
        incf *incfexecute = new incf(decoded);
        delete incfexecute;
    }
    if (decoded.cmd == "MOVF") {
        movf *movfexecute = new movf(decoded);
        delete movfexecute;
    }
    if (decoded.cmd == "CLRW") {
        clrw *clrwexecute = new clrw(decoded);
        delete clrwexecute;
    }
    if (decoded.cmd == "IORWF") {
        iorwf *iorwfexecute = new iorwf(decoded);
        delete iorwfexecute;
    }
    if (decoded.cmd == "XORWF") {
        xorwf *xorwfexecute = new xorwf(decoded);
        delete xorwfexecute;
    }
    if (decoded.cmd == "SUBWF") {
        subwf *subwfexecute = new subwf(decoded);
        delete subwfexecute;
    }
    if (decoded.cmd == "SWAPF") {
        swapf *swapfexecute = new swapf(decoded);
        delete swapfexecute;
    }
    if (decoded.cmd == "INCFSZ") {
        incfsz *incfszexecute = new incfsz(decoded);
        delete incfszexecute;
    }
    if (decoded.cmd == "DECFSZ") {
        decfsz *decfszexecute = new decfsz(decoded);
        delete decfszexecute;
    }
    if (decoded.cmd == "BSF") {
        bsf *bsfexecute = new bsf(decoded);
        delete bsfexecute;
    }
    if (decoded.cmd == "BCF") {
        bcf *bcfexecute = new bcf(decoded);
        delete bcfexecute;
    }
    if (decoded.cmd == "BTFSC") {
        btfsc *btfscexecute = new btfsc(decoded);
        delete btfscexecute;
    }
    if (decoded.cmd == "BTFSS") {
        btfss *btfssexecute = new btfss(decoded);
        delete btfssexecute;
    }
    if (decoded.cmd == "RETFIE") {
        retfie *retfieexecute = new retfie(decoded);
        delete retfieexecute;
    }
}
int picSim::run(std::string path, int guicounter) {
    inputfile file(path);
    file.readFile();
    thecommand = file.commandarray[guicounter];
    decode decode1(thecommand);
    if (ram1->getRam(129).test(5) == 1) // Timer aus?
    {
        picData1->setCycle(0);
    }
    oldPrescale = ram1->prescaler();
    executecmd(decode1.decodeCommand());
    rb47interrupt();
    setoldrb47();
    newPrescale = ram1->prescaler();
    if (oldPrescale != newPrescale) {
        picData1->setCycle(1);
    }
    timer();
    edge = detectedge(oldedge, 0);
    rb0interrupt();
    return picData1->getProgramCounter().to_ulong();
}
void picSim::timer() {
    if (ram1->getRam(129).test(5) == 0) {
        if (picData1->getCycle() >= ram1->prescaler()) {
            picData1->setCycle(picData1->getCycle() - ram1->prescaler());
            ram1->setRam(1, ram1->getRam(1).to_ulong() + 1);
            if (ram1->getRam(1) == 0) {
                // Timer Interrupt
                if (ram1->getRam(11).test(7) == 1) { // GIE erlaubt?
                    if (ram1->getRam(11).test(5) == 1) { // T0IE is Timer Interrupt enabled?
                        ram1->modifyBit(11, 2, true); // set T0IF
                        ram1->modifyBit(11, 7, false); // GIE auf 0 ziehen um Interrupts zu sperren
                        customStack1->push(
                                picData1->getProgramCounter().to_ulong()); // aktueller counter auf stack pushen
                        picData1->setProgramCounter(4); // 4 in PC
                    }
                }
            }
        }
    } else {
        // RA4 Timer
    }
}
void picSim::setoldrb47() {
    if (ram1->getRam(6).test(4) == 1) {
        rb4 = true;
    } else {
        rb4 = false;
    }
    if (ram1->getRam(6).test(5) == 1) {
        rb5 = true;
    } else {
        rb5 = false;
    }
    if (ram1->getRam(6).test(6) == 1) {
        rb6 = true;
    } else {
        rb6 = false;
    }
    if (ram1->getRam(6).test(7) == 1) {
        rb7 = true;
    } else {
        rb7 = false;
    }
}
void picSim::rb47interrupt() {
    if (ram1->getRam(11).test(7) == 1) { // GIE erlaubt?
        if (ram1->getRam(11).test(3) == 1) { // RBIE enabled??

            if (ram1->getRam(134).test(7) == 1 && rb7 != ram1->getRam(6).test(7)) {
                // Interrupt
                ram1->modifyBit(11, 7, false); // GIE auf 0 ziehen um Interrupts zu sperren
                ram1->modifyBit(11, 0, true); // RBIF set Interrupt aufgetreten?
                customStack1->push(picData1->getProgramCounter().to_ulong()); // aktueller counter auf stack pushen
                picData1->setProgramCounter(4); // 4 in PC
            }
            if (ram1->getRam(134).test(6) == 1 && rb6 != ram1->getRam(6).test(6)) {
                // Interrupt
                ram1->modifyBit(11, 7, false); // GIE auf 0 ziehen um Interrupts zu sperren
                ram1->modifyBit(11, 0, true); // RBIF set Interrupt aufgetreten?
                customStack1->push(picData1->getProgramCounter().to_ulong()); // aktueller counter auf stack pushen
                picData1->setProgramCounter(4); // 4 in PC
            }
            if (ram1->getRam(134).test(5) == 1 && rb5 != ram1->getRam(6).test(5)) {
                // Interrupt
                ram1->modifyBit(11, 7, false); // GIE auf 0 ziehen um Interrupts zu sperren
                ram1->modifyBit(11, 0, true); // RBIF set Interrupt aufgetreten?
                customStack1->push(picData1->getProgramCounter().to_ulong()); // aktueller counter auf stack pushen
                picData1->setProgramCounter(4); // 4 in PC
            }
            if (ram1->getRam(134).test(4) == 1 && rb4 != ram1->getRam(6).test(4)) {
                // Interrupt
                ram1->modifyBit(11, 7, false); // GIE auf 0 ziehen um Interrupts zu sperren
                ram1->modifyBit(11, 0, true); // RBIF set Interrupt aufgetreten?
                customStack1->push(picData1->getProgramCounter().to_ulong()); // aktueller counter auf stack pushen
                picData1->setProgramCounter(4); // 4 in PC
            }
        }
    }
}
void picSim::rb0interrupt() {
    if (ram1->getRam(11).test(7) == 1) { // GIE erlaubt?
        if (ram1->getRam(11).test(4) == 1) { // Interrupt RB0 enabled?
            if (ram1->getRam(129).test(6)) {
                IntEdg = 1;
            } else {
                IntEdg = 0;
            }
            if (IntEdg == edge) { // interrupt?
                ram1->modifyBit(11, 1, true); // INTF set Interrupt aufgetreten?
                ram1->modifyBit(11, 7, false); // GIE auf 0 ziehen um Interrupts zu sperren
                customStack1->push(picData1->getProgramCounter().to_ulong()); // aktueller counter auf stack pushen
                picData1->setProgramCounter(4); // 4 in PC
            }
        }
    }
}
int picSim::detectedge(int oldvalue, int port) {
    int portvalue;
    if (ram1->getRam(6).test(port)) {
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
    picData1->setWreg(0);
    picData1->setCycle(ram1->setRam(2, 0, picData1->getCycle()));
    if (type) {
        ram1->modifyBit(3, 7, false);
        ram1->modifyBit(3, 6, false);
        ram1->modifyBit(3, 5, false);
        ram1->modifyBit(3, 4, true);
        ram1->modifyBit(3, 3, true);
        ram1->modifyBit(131, 7, false);
        ram1->modifyBit(131, 6, false);
        ram1->modifyBit(131, 5, false);
        ram1->modifyBit(131, 4, true);
        ram1->modifyBit(131, 3, true);
    } else {
        ram1->modifyBit(3, 7, false);
        ram1->modifyBit(3, 6, false);
        ram1->modifyBit(3, 5, false);
        ram1->modifyBit(131, 7, false);
        ram1->modifyBit(131, 6, false);
        ram1->modifyBit(131, 5, false);
    }
    picData1->setCycle(ram1->setRam(10, 0, picData1->getCycle()));
    picData1->setCycle(ram1->setRam(11, 0, picData1->getCycle()));
    picData1->setCycle(ram1->setRam(129, 255, picData1->getCycle()));
    picData1->setCycle(ram1->setRam(133, 255, picData1->getCycle()));
    picData1->setCycle(ram1->setRam(134, 255, picData1->getCycle()));
    picData1->setProgramCounter(0);
}
int picSim::ping(int ramIndex) {
    return ram1->getRamGui(ramIndex).to_ulong();
}
int picSim::getPSA() {
    return newPrescale;
}
void picSim::resetRuntime() {
    picData1->setRuntime(0);
}
std::string picSim::showPCLATH() {
    std::string PCLATH8;
    std::string PCLATH5;
    std::string PCL;
    std::string PC;
    PCLATH8 = ram1->getRam(10).to_string();
    PCLATH5 = PCLATH8.substr(3, 5);
    PCL = ram1->getRam(2).to_string();
    PC = PCLATH5 + PCL;
    return PC;
}
std::string picSim::getPCLATH() {
    std::string PCLATH8;
    std::string PCLATH5;
    PCLATH8 = ram1->getRam(10).to_string();
    PCLATH5 = PCLATH8.substr(3, 5);
    return PCLATH5;
}
void picSim::createPC(int filepos_m) {
    if (filepos_m == 2) {
        std::string PCLATH = ram1->getRam(10).to_string();
        std::string PCL = ram1->getRam(2).to_string();
        std::string PCLATH40 = PCLATH.substr(3, 5);
        std::string PCstring = PCLATH40 + PCL;
        PC PCbits = std::stoi(PCstring, 0, 2);
        picData1->setProgramCounter(PCbits.to_ulong());
    } else {
        picData1->setProgramCounter(picData1->getProgramCounter().to_ulong());
    }
}
BYTE picSim::createPCL() {
    std::string PCstring = picData1->getProgramCounter().to_string();
    std::string PCL = PCstring.substr(5, 8);
    BYTE PCLreturn = stoi(PCL, 0, 2);
    return PCLreturn;
}
std::string picSim::pclath43() {
    std::string PCLATH = ram1->getRam(10).to_string();
    std::string PCLATH43 = PCLATH.substr(0, 2);
    return PCLATH43;
}
void picSim::reset() {
    picData1->setCycle(0);
    oldPrescale = 0;
    newPrescale = 0;
    oldedge = 0;
    picData1->setRuntime(0);
    customStack1->clearStack();
    resetRuntime();
}