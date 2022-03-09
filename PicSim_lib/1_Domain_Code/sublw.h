#ifndef ASE_PICSIM_SUBLW_H
#define ASE_PICSIM_SUBLW_H

#include <bitset>
#include "command.h"

typedef std::bitset<8> BYTE;
typedef std::bitset<13> PC;

class sublw : public command {
public:
    void executeCMD(decodedCmdSimple ldecoded) override;
};

#endif //ASE_PICSIM_SUBLW_H
