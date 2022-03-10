#ifndef ASE_PICSIM_CMDCALL_H
#define ASE_PICSIM_CMDCALL_H

#include <bitset>
#include "command.h"

typedef std::bitset<8> BYTE;
typedef std::bitset<13> PC;

class cmdcall : public command {
public:
    void logic(decodedCmdSimple ldecoded) override;
    void updateProgramCounter() override;
private:
    std::string inttobin;
};

#endif //ASE_PICSIM_CMDCALL_H
