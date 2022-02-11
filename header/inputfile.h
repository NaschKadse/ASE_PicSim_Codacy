#ifndef PICSIM2_0_INPUTFILE_H
#define PICSIM2_0_INPUTFILE_H


#include <iostream>
#include <utility>
#include <fstream>
#include "utility.h"


class inputfile {
private:
    std::string filepath_l;
public:
    inputfile(std::string filepath);
    ~inputfile();
    std::string commandarray[1024];
    std::string *readFile();



};


#endif //PICSIM2_0_INPUTFILE_H
