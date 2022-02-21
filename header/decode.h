#ifndef PICSIM2_0_DECODE_H
#define PICSIM2_0_DECODE_H

#include <string>
#include <utility>

class decode {
public:
    decode(std::string inputCmd);
    ~decode();
    struct decodedCmd {
        std::string cmd;
        int dBit;
        int filepos;
        int literal;
    };
    decodedCmd decodeCommand();
private:
    std::string toDecode;
};

#endif //PICSIM2_0_DECODE_H
