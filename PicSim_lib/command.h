#ifndef ASE_PICSIM_COMMAND_H
#define ASE_PICSIM_COMMAND_H

#include <string>
#include "utility.h"

struct decodedCmdSimple {
    std::string cmd;
    int dBit;
    int filepos;
    int literal;
};

class command {
public:
    virtual void executeCMD(decodedCmdSimple simpleDecodedStruct) = 0;
};

#endif //ASE_PICSIM_COMMAND_H
