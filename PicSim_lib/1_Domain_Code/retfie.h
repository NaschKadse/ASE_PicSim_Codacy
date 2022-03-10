#ifndef ASE_PICSIM_RETFIE_H
#define ASE_PICSIM_RETFIE_H

#include <bitset>
#include "command.h"

typedef std::bitset<8> BYTE;
typedef std::bitset<13> PC;

class retfie : public command {
public:
    void logic(decodedCmdSimple ldecoded) override;
    void updateProgramCounter() override;
};

#endif //ASE_PICSIM_RETFIE_H
