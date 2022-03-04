#ifndef ASE_PICSIM_LSTFILEHANDLER_H
#define ASE_PICSIM_LSTFILEHANDLER_H

#include <iostream>
#include <utility>
#include <fstream>
#include "utility.h"
#include "readFileInterface.h"
#include "picData.h"

class LSTFileHandler : public readFileInterface {
public:
    void readFile(std::string filepath);
private:
    picData *picData1 = picData::getPicDataObject();

};

#endif //ASE_PICSIM_LSTFILEHANDLER_H
