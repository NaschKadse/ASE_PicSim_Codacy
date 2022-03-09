#ifndef ASE_PICSIM_BSF_H
#define ASE_PICSIM_BSF_H

#include <bitset>
#include "command.h"

typedef std::bitset<8> BYTE;
typedef std::bitset<13> PC;

class bsf : public command {
public:
    void executeCMD(decodedCmdSimple ldecoded) override;
private:
    ram *ramlocal = ram::getRamObject();
    picData *picDatalocal = picData::getPicDataObject();
};

#endif //ASE_PICSIM_BSF_H
