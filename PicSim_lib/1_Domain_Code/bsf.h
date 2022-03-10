#ifndef ASE_PICSIM_BSF_H
#define ASE_PICSIM_BSF_H

#include <bitset>
#include "command.h"

typedef std::bitset<8> BYTE;
typedef std::bitset<13> PC;

class bsf : public command {
public:
    void logic(decodedCmdSimple ldecoded) override;
    void updateProgramCounter() override;
};

#endif //ASE_PICSIM_BSF_H
