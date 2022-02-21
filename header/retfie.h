#ifndef ASE_PICSIM_RETFIE_H
#define ASE_PICSIM_RETFIE_H

#include <bitset>
#include "picData.h"
#include "picSim.h"
#include "customStack.h"

typedef std::bitset<8> BYTE;
typedef std::bitset<13> PC;

class retfie : public picSim {
public:
    void execute(const decode::decodedCmd &ldecoded);
    explicit retfie(decode::decodedCmd ldecoded) {
        execute(ldecoded);
    };
private:
    ram *ramlocal = ram::getRamObject();
    customStack *customStacklocal = customStack::getcustomStackObject();
    picData *picDatalocal = picData::getPicDataObject();
};

#endif //ASE_PICSIM_RETFIE_H
