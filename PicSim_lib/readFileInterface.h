
#ifndef ASE_PICSIM_READFILEINTERFACE_H
#define ASE_PICSIM_READFILEINTERFACE_H

#include <string>

class readFileInterface {
public:
    virtual void readFile(std::string filepath) = 0;
};

#endif //ASE_PICSIM_READFILEINTERFACE_H
