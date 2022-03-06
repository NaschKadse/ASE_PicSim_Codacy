#include "picSim.h"
#include "readFileInterface.h"
#include "3_Plugins/LSTFileHandler.h"
#include "2_Application_Code/handler.h"

void picSim::executecmd(decode::decodedCmd decoded) {
    decodedCmdSimple localstruct;
    localstruct.cmd = decoded.cmd;
    localstruct.dBit = decoded.dBit;
    localstruct.literal = decoded.literal;
    localstruct.filepos = decoded.filepos;
    decoded.cmdobject->executeCMD(localstruct);
    delete decoded.cmdobject;
}
int picSim::run(std::string path, int guicounter) {
    LSTFileHandler lsthandler;
    handler inputhandler(&lsthandler);
    utility *bla = new utility;
    inputhandler.read(path, *bla);
    thecommand = picData1->getCommandArray(guicounter);
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
            BYTE ramhelper1 = ram1->getRam(134);
            BYTE ramhelper2 = ram1->getRam(6);
            if (ramhelper1.test(7) == 1 && rb7 != ramhelper2.test(7) ||
                ramhelper1.test(6) == 1 && rb6 != ramhelper2.test(6) ||
                ramhelper1.test(5) == 1 && rb5 != ramhelper2.test(5) ||
                ramhelper1.test(4) == 1 && rb4 != ramhelper2.test(4)) {
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
bool picSim::checkFilepos(int filepos_m){
    if(filepos_m == 2){
        return true;
    }
    return false;
}

int picSim::createPC(const std::string filepos10, std::string filepos2) {
    std::string PCLATH = filepos10;
    std::string PCL = filepos2;
    std::string PCLATH40 = PCLATH.substr(3, 5);
    std::string PCstring = PCLATH40 + PCL;
    PC PCbits = std::stoi(PCstring, 0, 2);
    return PCbits.to_ulong();
}
BYTE picSim::createPCL(std::string PCstring) {
    std::string PCL = PCstring.substr(5, 8);
    BYTE PCLreturn = stoi(PCL, 0, 2);
    return PCLreturn;
}
std::string picSim::pclath43(std::string PCLATH) {
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

