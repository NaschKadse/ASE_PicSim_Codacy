#ifndef PICSIM2_0_PICSIM_H
#define PICSIM2_0_PICSIM_H

#include "2_Application_Code/decode.h"
#include "0_Abstraction_Code/ram.h"
#include "stack"
#include "bitset"
#include "0_Abstraction_Code/customStack.h"
#include <array>

typedef std::bitset<8> BYTE;
typedef std::bitset<13> PC;

class picSim {
public:
    int ping(int ramIndex);
    int run(std::string path, int guicounter);
    int getPSA();
    void init(bool type);
    void resetRuntime();
    std::string showPCLATH();
    std::string getPCLATH();
    void reset();
    void setoldrb47();
    void rb47interrupt();
    static bool checkFilepos(int filepos_m);
    static int createPC(std::string filepos10, std::string filepos2);
    static BYTE createPCL(std::string PCstring);
    static std::string pclath43(std::string PCLATH);
    int getIntEdg();
    void rb0interrupt();
    void executecmd(decode::decodedCmd decoded);
    void setEdge(bool set);
    int getEdge();

private:
    std::string thecommand;
    customStack *customStack1 = customStack::getcustomStackObject();
    picData *picData1 = picData::getPicDataObject();
    ram *ram1 = ram::getRamObject();
    int oldPrescale = 0;
    int newPrescale = 0;
    int edge = 0;
    int oldedge = 0;
    bool rb4;
    bool rb5;
    bool rb6;
    bool rb7;
    int IntEdg;
    int detectedge(int oldvalue, int port);
    void timer();

};

#endif //PICSIM2_0_PICSIM_H
