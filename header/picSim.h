#ifndef PICSIM2_0_PICSIM_H
#define PICSIM2_0_PICSIM_H


#include "inputfile.h"
#include "decode.h"
#include "myStack.h"
#include "ram.h"
#include "stack"
#include "bitset"
#include <array>



class picSim {

public:
    typedef std::bitset<8> BYTE;
    typedef std::bitset<13> PC;

    myStack stack1;
    BYTE wreg = 0;
    PC programCounter = 0;


    int ping(int ramIndex);
    int run(std::string path, int guicounter);
    int getPSA();
    int getCycles();

    void init(bool type);
    void ramInput(std::string input, int buttonNumber);
    void ramBitInput(int registerNo, int bit, bool set);
    void setWreg(std::string input);
    void setMultiplier(float mult);
    void resetRuntime();

    BYTE getWreg();

    std::array<int, 200> stackarray = { 0 };

    std::string getBit(int registerNo, int bit);
    std::string showPCLATH();
    std::string getPCLATH();

    int getRam(int filepos);

    unsigned long getPC();

    float getRuntime();
    float getMultiplier();

    void reset();
    void setPC();
    void setoldrb47();
    void rb47interrupt();
    void clearStack();
    void clearRAM();
    void createPC(int filepos_m);

    PC getStack(int pos);

protected:
    ram ram1;

private:
    void executecmd(decode::decodedCmd decoded);
    std::string thecommand;
    std::stack<int> callstack;

    int cycle =0;
    int oldPrescale = 0;
    int newPrescale = 0;
    int edge = 0;
    int oldedge = 0;

    float runtime = 0;
    float multiplier = 1.000;

    bool rb4;
    bool rb5;
    bool rb6;
    bool rb7;
    int IntEdg;

    int detectedge(int oldvalue, int port);
    void nop();
    void timer();
    void rb0interrupt();
    BYTE createPCL();
    std::string pclath43();
};


#endif //PICSIM2_0_PICSIM_H
