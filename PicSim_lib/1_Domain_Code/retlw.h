#ifndef ASE_PICSIM_RETLW_H
#define ASE_PICSIM_RETLW_H

#include <bitset>
#include "0_Abstraction_Code/picData.h"
#include "2_Application_Code/picSim.h"
#include "0_Abstraction_Code/customStack.h"

typedef std::bitset<8> BYTE;
typedef std::bitset<13> PC;

class retlw : public command {
public:
    void executeCMD(decodedCmdSimple ldecoded);
private:
    ram *ramlocal = ram::getRamObject();
    customStack *customStacklocal = customStack::getcustomStackObject();
    picData *picDatalocal = picData::getPicDataObject();
};

#endif //ASE_PICSIM_RETLW_H
