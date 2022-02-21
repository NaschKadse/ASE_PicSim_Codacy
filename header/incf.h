#ifndef ASE_PICSIM_INCF_H
#define ASE_PICSIM_INCF_H

#include <bitset>
#include "picData.h"
#include "picSim.h"

typedef std::bitset<8> BYTE;
typedef std::bitset<13> PC;

class incf : public picSim {
public:
    void execute(const decode::decodedCmd &ldecoded);
    explicit incf(decode::decodedCmd ldecoded) {
        execute(ldecoded);
    };
private:
    ram *ramlocal = ram::getRamObject();
    picData *picDatalocal = picData::getPicDataObject();
};

#endif //ASE_PICSIM_INCF_H
