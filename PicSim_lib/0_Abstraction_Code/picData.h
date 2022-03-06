//
// Created by win on 11.02.2022.
//

#ifndef ASE_PICSIM_PICDATA_H
#define ASE_PICSIM_PICDATA_H

#include <bitset>

typedef std::bitset<8> BYTE;
typedef std::bitset<13> PC;

class picData {
public:
    static picData *getPicDataObject();
    void setWreg(BYTE lwreg);
    BYTE getWreg();
    void setProgramCounter(PC lprogrammCounter);
    PC getProgramCounter();
    void setCycle(int lcycle);
    int getCycle();
    void setRuntime(float lruntime);
    float getRuntime();
    void setMultiplier(float lmultiplier);
    float getMultiplier();
    void setCommandArray(int pos, std::string larray);
    std::string getCommandArray(int pos);
    void releaseInstance();
private:
    picData() {};
    ~picData() {};
    static picData *picDataObject;
    BYTE wreg = 0;
    PC programmCounter = 0;
    int cycle = 0;
    float runtime = 0;
    float multiplier = 1.000;
    std::string commandarray[1024] = {};
};

#endif //ASE_PICSIM_PICDATA_H
