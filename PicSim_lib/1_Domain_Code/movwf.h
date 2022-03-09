#ifndef ASE_PICSIM_MOVWF_H
#define ASE_PICSIM_MOVWF_H

#include <bitset>
#include "command.h"

typedef std::bitset<8> BYTE;
typedef std::bitset<13> PC;

class movwf : public command {
public:
    void executeCMD(decodedCmdSimple ldecoded) override;
};

#endif //ASE_PICSIM_MOVWF_H
