#ifndef PICSIM2_0_UTILITY_H
#define PICSIM2_0_UTILITY_H

#include <string>
#include <bitset>
#include <iostream>

typedef std::bitset<8> BYTE;

class utility {
private:
    int tobin_l = 0;
    int digits_l = 0;
    std::string tofill_l = "";
public:
    //utility(int tobin);
    //utility(std::string tofill, int digits);
    ~utility();
    virtual std::string toBinary();
    virtual std::string fillup();
    static void debugprint1(std::string cmd, BYTE pcl, int literal, std::string cmdbin);
    virtual void setToBin(int tobin);
    virtual void setDigits(int digits);
    virtual void setToFill(std::string tofill);
};

#endif //PICSIM2_0_UTILITY_H
