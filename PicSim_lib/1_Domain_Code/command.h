#ifndef ASE_PICSIM_COMMAND_H
#define ASE_PICSIM_COMMAND_H

#include <string>
#include "2_Application_Code/utility.h"

struct decodedCmdSimple {
    std::string cmd;
    int dBit;
    int filepos;
    int literal;
};

class command {
public:
    virtual void executeCMD(decodedCmdSimple simpleDecodedStruct) = 0;
    virtual ~command() {}
};

#endif //ASE_PICSIM_COMMAND_H
