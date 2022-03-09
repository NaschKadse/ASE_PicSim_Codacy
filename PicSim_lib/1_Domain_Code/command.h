#ifndef ASE_PICSIM_COMMAND_H
#define ASE_PICSIM_COMMAND_H

#include <string>
#include "2_Application_Code/utility.h"
#include "0_Abstraction_Code/ram.h"
#include "0_Abstraction_Code/customStack.h"

struct decodedCmdSimple {
    std::string cmd;
    int dBit;
    int filepos;
    int literal;
};

class command {
public:
    virtual void executeCMD(decodedCmdSimple simpleDecodedStruct) = 0;
    virtual ~command() = default;
protected:
    void increasePC() const;
    void increasePC(std::string inttobin) const;
    void increaseCycle1() const;
    void increaseCycle2() const;
    void increaseRuntime() const;
    void increaseRuntime2() const;
    static int createPC(const std::string filepos10, std::string filepos2);
    static bool checkFilepos(int filepos_m);
    static std::string pclath43(std::string PCLATH);
    ram *ramlocal = ram::getRamObject();
    picData *picDatalocal = picData::getPicDataObject();
    customStack *customStacklocal = customStack::getcustomStackObject();
private:
    static BYTE createPCL(const std::string &PCstring);
};

#endif //ASE_PICSIM_COMMAND_H
