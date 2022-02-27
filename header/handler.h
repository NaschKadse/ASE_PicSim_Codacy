#ifndef ASE_PICSIM_HANDLER_H
#define ASE_PICSIM_HANDLER_H

#include <string>
#include "readFileInterface.h"

class handler {
public:
    handler(readFileInterface *handlerobject) {
        localhandler = handlerobject;
    }
    void read(std::string filepath);
private:
    readFileInterface *localhandler;
};

#endif //ASE_PICSIM_HANDLER_H
