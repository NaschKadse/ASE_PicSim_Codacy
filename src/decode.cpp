#include "../header/decode.h"

decode::decode(std::string inputCmd) {
    this->toDecode = std::move(inputCmd);
}
decode::~decode() = default;
decode::decodedCmd decode::decodeCommand() {
    decodedCmd decodeCommand;


    // RETFIE
    if (this->toDecode.substr(0, 14) == "00000000001001") {
        decodeCommand.cmd = "RETFIE";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = -1;
    }

    // RETURN
    if (this->toDecode.substr(0, 14) == "00000000001000") {
        decodeCommand.cmd = "RETURN";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = -1;
    }

    // NOP
    if (this->toDecode.substr(0, 7) == "0000000" && this->toDecode.substr(9, 5) == "00000") {
        decodeCommand.cmd = "NOP";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = -1;
    }

    // CLRF
    if (this->toDecode.substr(0, 7) == "0000011") {
        decodeCommand.cmd = "CLRF";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
    }

    // CLRW
    if (this->toDecode.substr(0, 7) == "0000010") {
        decodeCommand.cmd = "CLRW";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = -1;
    }

    // MOVWF
    if (this->toDecode.substr(0, 7) == "0000001") {
        decodeCommand.cmd = "MOVWF";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
    }

    //SUBWF
    if (this->toDecode.substr(0, 6) == "000010") {
        decodeCommand.cmd = "SUBWF";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
    }

    // IORWF
    if (this->toDecode.substr(0, 6) == "000100") {
        decodeCommand.cmd = "IORWF";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
    }

    // MOVF
    if (this->toDecode.substr(0, 6) == "001000") {
        decodeCommand.cmd = "MOVF";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
    }

    // SWAPF
    if (this->toDecode.substr(0, 6) == "001110") {
        decodeCommand.cmd = "SWAPF";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
    }

    // ADDWF
    if (this->toDecode.substr(0, 6) == "000111") {
        decodeCommand.cmd = "ADDWF";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
    }

    // ANDWF
    if (this->toDecode.substr(0, 6) == "000101") {
        decodeCommand.cmd = "ANDWF";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
    }

    // ANDLW
    if (this->toDecode.substr(0, 6) == "111001") {
        decodeCommand.cmd = "ANDLW";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = stoi(this->toDecode.substr(6, 8), nullptr, 2);
    }

    // DECFSZ
    if (this->toDecode.substr(0, 6) == "001011") {
        decodeCommand.cmd = "DECFSZ";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
    }

    // INCFSZ
    if (this->toDecode.substr(0, 6) == "001111") {
        decodeCommand.cmd = "INCFSZ";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
    }

    // COMF
    if (this->toDecode.substr(0, 6) == "001001") {
        decodeCommand.cmd = "COMF";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
    }

    // IORLW
    if (this->toDecode.substr(0, 6) == "111000") {
        decodeCommand.cmd = "IORLW";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = stoi(this->toDecode.substr(6, 9), nullptr, 2);
    }

    // DECF
    if (this->toDecode.substr(0, 6) == "000011") {
        decodeCommand.cmd = "DECF";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
    }

    // INCF
    if (this->toDecode.substr(0, 6) == "001010") {
        decodeCommand.cmd = "INCF";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
    }

    // XORLW
    if (this->toDecode.substr(0, 6) == "111010") {
        decodeCommand.cmd = "XORLW";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = stoi(this->toDecode.substr(6, 8), nullptr, 2);
    }

    // RRF
    if (this->toDecode.substr(0, 6) == "001100") {
        decodeCommand.cmd = "RRF";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
    }

    // RLF
    if (this->toDecode.substr(0, 6) == "001101") {
        decodeCommand.cmd = "RLF";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
    }

    // XORWF
    if (this->toDecode.substr(0, 6) == "000110") {
        decodeCommand.cmd = "XORWF";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
    }

    // SUBLW
    if (this->toDecode.substr(0, 5) == "11110") {
        decodeCommand.cmd = "SUBLW";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = stoi(this->toDecode.substr(6, 8), nullptr, 2);
    }

    // ADDLW
    if (this->toDecode.substr(0, 5) == "11111") {
        decodeCommand.cmd = "ADDLW";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = stoi(this->toDecode.substr(6, 8), nullptr, 2);
    }

    // BTFSC
    if (this->toDecode.substr(0, 4) == "0110") {
        decodeCommand.cmd = "BTFSC";
        decodeCommand.literal = stoi(this->toDecode.substr(4, 3), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.dBit = -1;
    }

    // BTFSS
    if (this->toDecode.substr(0, 4) == "0111") {
        decodeCommand.cmd = "BTFSS";
        decodeCommand.literal = stoi(this->toDecode.substr(4, 3), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.dBit = -1;
    }

    // BCF
    if (this->toDecode.substr(0, 4) == "0100") {
        decodeCommand.cmd = "BCF";
        decodeCommand.literal = stoi(this->toDecode.substr(4, 3), nullptr, 2);
        decodeCommand.filepos = (stoi(this->toDecode.substr(7, 7), nullptr, 2));
        decodeCommand.dBit = -1;
    }

    // BSF
    if (this->toDecode.substr(0, 4) == "0101") {
        decodeCommand.cmd = "BSF";
        decodeCommand.literal = stoi(this->toDecode.substr(4, 3), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.dBit = -1;
    }

    // RETLW
    if (this->toDecode.substr(0, 4) == "1101") {
        decodeCommand.cmd = "RETLW";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = stoi(this->toDecode.substr(6, 8), nullptr, 2);
    }

    // MOVLW
    if (this->toDecode.substr(0, 4) == "1100") {
        decodeCommand.cmd = "MOVLW";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = stoi(this->toDecode.substr(6, 8), nullptr, 2);
    }

    // CALL
    if (this->toDecode.substr(0, 3) == "100") {
        decodeCommand.cmd = "CALL";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = stoi(this->toDecode.substr(3, 11), nullptr, 2);
    }

    // GOTO
    if (this->toDecode.substr(0, 3) == "101") {
        decodeCommand.cmd = "GOTO";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = stoi(this->toDecode.substr(3, 11), nullptr, 2);
    }
    return decodeCommand;
}



