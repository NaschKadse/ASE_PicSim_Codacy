#include "utility.h"

utility::utility(int tobin) {
    this->tobin_l = tobin;
}
utility::utility(std::string tofill, int digits) {
    this->tofill_l = std::move(tofill);
    this->digits_l = digits;
}
utility::~utility() = default;
std::string utility::toBinary() {
    std::string returnString;
    while (this->tobin_l != 0) {
        returnString = (this->tobin_l % 2 == 0 ? "0" : "1") + returnString;
        this->tobin_l /= 2;
    }
    return returnString;
}
std::string utility::fillup() {
    for (int i = 0; this->tofill_l.length() < this->digits_l; i++) {
        this->tofill_l = "0" + this->tofill_l;
    }
    return this->tofill_l;
}
const unsigned char ae = static_cast<unsigned char>(132);
const unsigned char ue = static_cast<unsigned char>(129);
void utility::debugprint1(const std::string cmd, BYTE pcl, int value, std::string cmdbin) {
    int cmdint = std::stoi(cmdbin, 0, 2);
    std::cout << "------------------------------------------------------\n";
    std::printf("|  %c %c %c    N%cchster Befehl zum Ausf%chren     %c %c %c  |\n", 31, 31, 31, ae, ue, 31, 31, 31);
    std::cout << "------------------------------------------------------\n\n";
    std::printf("%c %04lX %04X ", 16, pcl.to_ulong(), cmdint);
    std::cout << cmd;
    if (value != -1) {
        std::printf(" %02Xh", value);
    }
    std::cout << "\n";
}



