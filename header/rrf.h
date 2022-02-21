#ifndef ASE_PICSIM_RRF_H
#define ASE_PICSIM_RRF_H

#include <bitset>
#include "picData.h"
#include "picSim.h"

typedef std::bitset<8> BYTE;
typedef std::bitset<13> PC;

class rrf : public picSim {
public:
    void execute(const decode::decodedCmd &ldecoded);
    explicit rrf(decode::decodedCmd ldecoded) {
        execute(ldecoded);
    };
private:
    ram *ramlocal = ram::getRamObject();
    picData *picDatalocal = picData::getPicDataObject();
};

#endif //ASE_PICSIM_RRF_H
