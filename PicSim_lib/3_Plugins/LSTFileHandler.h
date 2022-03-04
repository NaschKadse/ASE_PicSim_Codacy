#ifndef ASE_PICSIM_LSTFILEHANDLER_H
#define ASE_PICSIM_LSTFILEHANDLER_H

#include <iostream>
#include <utility>
#include <fstream>
#include "2_Application_Code/utility.h"
#include "2_Application_Code/readFileInterface.h"
#include "0_Abstraction_Code/picData.h"

class LSTFileHandler : public readFileInterface {
public:
    void readFile(std::string filepath);
private:
    picData *picData1 = picData::getPicDataObject();

};

#endif //ASE_PICSIM_LSTFILEHANDLER_H
