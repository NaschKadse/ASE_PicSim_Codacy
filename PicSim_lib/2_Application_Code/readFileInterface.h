
#ifndef ASE_PICSIM_READFILEINTERFACE_H
#define ASE_PICSIM_READFILEINTERFACE_H

#include <string>
#include "2_Application_Code/utility.h"

class readFileInterface {
public:
    virtual void readFile(std::string filepath, utility &utility1) = 0;
};

#endif //ASE_PICSIM_READFILEINTERFACE_H
