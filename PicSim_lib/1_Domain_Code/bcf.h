#ifndef ASE_PICSIM_BCF_H
#define ASE_PICSIM_BCF_H

#include <bitset>
#include "0_Abstraction_Code/picData.h"
#include "2_Application_Code/picSim.h"

typedef std::bitset<8> BYTE;
typedef std::bitset<13> PC;

class bcf : public command {
public:
    void executeCMD(decodedCmdSimple ldecoded);
private:
    ram *ramlocal = ram::getRamObject();
    picData *picDatalocal = picData::getPicDataObject();
};

#endif //ASE_PICSIM_BCF_H
