#ifndef PICSIM2_0_UTILITY_H
#define PICSIM2_0_UTILITY_H


#include <string>
#include <bitset>
#include <iostream>


typedef std::bitset<8> BYTE;

class utility {
private:
    int tobin_l{};
    int digits_l{};
    std::string tofill_l;
public:

    utility(int tobin);

    utility(std::string tofill, int digits);

    ~utility();

    std::string toBinary();

    std::string fillup();

    static void debugprint1(std::string cmd, BYTE pcl, int literal, std::string cmdbin);
};


#endif //PICSIM2_0_UTILITY_H
