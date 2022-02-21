#ifndef ASE_PICSIM_CMDRETURN_H
#define ASE_PICSIM_CMDRETURN_H

#include <bitset>
#include "picData.h"
#include "picSim.h"
#include "customStack.h"

typedef std::bitset<8> BYTE;
typedef std::bitset<13> PC;

class cmdreturn : public picSim {
public:
    void execute(const decode::decodedCmd &ldecoded);
    explicit cmdreturn(decode::decodedCmd ldecoded) {
        execute(ldecoded);
    };
private:
    ram *ramlocal = ram::getRamObject();
    customStack *customStacklocal = customStack::getcustomStackObject();
    picData *picDatalocal = picData::getPicDataObject();
};

#endif //ASE_PICSIM_CMDRETURN_H
