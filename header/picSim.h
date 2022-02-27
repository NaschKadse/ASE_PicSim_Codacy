#ifndef PICSIM2_0_PICSIM_H
#define PICSIM2_0_PICSIM_H

#include "decode.h"
#include "ram.h"
#include "stack"
#include "bitset"
#include "customStack.h"
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
private:
    void executecmd(decode::decodedCmd decoded);
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
    void rb0interrupt();
};

#endif //PICSIM2_0_PICSIM_H
