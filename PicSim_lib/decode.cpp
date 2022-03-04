#include "decode.h"
#include "movlw.h"
#include "retfie.h"
#include "cmdreturn.h"
#include "nop.h"
#include "clrf.h"
#include "clrw.h"
#include "movwf.h"
#include "subwf.h"
#include "iorwf.h"
#include "movf.h"
#include "swapf.h"
#include "addwf.h"
#include "andwf.h"
#include "andlw.h"
#include "decfsz.h"
#include "incfsz.h"
#include "comf.h"
#include "iorlw.h"
#include "decf.h"
#include "incf.h"
#include "xorlw.h"
#include "rrf.h"
#include "rlf.h"
#include "xorwf.h"
#include "sublw.h"
#include "addlw.h"
#include "btfsc.h"
#include "btfss.h"
#include "bcf.h"
#include "bsf.h"
#include "retlw.h"
#include "cmdcall.h"
#include "cmdgo.h"

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
        decodeCommand.cmdobject = new retfie();
    }

    // RETURN
    if (this->toDecode.substr(0, 14) == "00000000001000") {
        decodeCommand.cmd = "RETURN";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new cmdreturn();
    }

    // NOP
    if (this->toDecode.substr(0, 7) == "0000000" && this->toDecode.substr(9, 5) == "00000") {
        decodeCommand.cmd = "NOP";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new nop();
    }

    // CLRF
    if (this->toDecode.substr(0, 7) == "0000011") {
        decodeCommand.cmd = "CLRF";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new clrf();
    }

    // CLRW
    if (this->toDecode.substr(0, 7) == "0000010") {
        decodeCommand.cmd = "CLRW";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new clrw();
    }

    // MOVWF
    if (this->toDecode.substr(0, 7) == "0000001") {
        decodeCommand.cmd = "MOVWF";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new movwf();
    }

    //SUBWF
    if (this->toDecode.substr(0, 6) == "000010") {
        decodeCommand.cmd = "SUBWF";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new subwf();
    }

    // IORWF
    if (this->toDecode.substr(0, 6) == "000100") {
        decodeCommand.cmd = "IORWF";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new iorwf();
    }

    // MOVF
    if (this->toDecode.substr(0, 6) == "001000") {
        decodeCommand.cmd = "MOVF";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new movf();
    }

    // SWAPF
    if (this->toDecode.substr(0, 6) == "001110") {
        decodeCommand.cmd = "SWAPF";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new swapf();
    }

    // ADDWF
    if (this->toDecode.substr(0, 6) == "000111") {
        decodeCommand.cmd = "ADDWF";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new addwf();
    }

    // ANDWF
    if (this->toDecode.substr(0, 6) == "000101") {
        decodeCommand.cmd = "ANDWF";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new andwf();
    }

    // ANDLW
    if (this->toDecode.substr(0, 6) == "111001") {
        decodeCommand.cmd = "ANDLW";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = stoi(this->toDecode.substr(6, 8), nullptr, 2);
        decodeCommand.cmdobject = new andlw();
    }

    // DECFSZ
    if (this->toDecode.substr(0, 6) == "001011") {
        decodeCommand.cmd = "DECFSZ";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new decfsz();
    }

    // INCFSZ
    if (this->toDecode.substr(0, 6) == "001111") {
        decodeCommand.cmd = "INCFSZ";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new incfsz();
    }

    // COMF
    if (this->toDecode.substr(0, 6) == "001001") {
        decodeCommand.cmd = "COMF";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new comf();
    }

    // IORLW
    if (this->toDecode.substr(0, 6) == "111000") {
        decodeCommand.cmd = "IORLW";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = stoi(this->toDecode.substr(6, 9), nullptr, 2);
        decodeCommand.cmdobject = new iorlw();
    }

    // DECF
    if (this->toDecode.substr(0, 6) == "000011") {
        decodeCommand.cmd = "DECF";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new decf();
    }

    // INCF
    if (this->toDecode.substr(0, 6) == "001010") {
        decodeCommand.cmd = "INCF";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new incf();
    }

    // XORLW
    if (this->toDecode.substr(0, 6) == "111010") {
        decodeCommand.cmd = "XORLW";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = stoi(this->toDecode.substr(6, 8), nullptr, 2);
        decodeCommand.cmdobject = new xorlw();
    }

    // RRF
    if (this->toDecode.substr(0, 6) == "001100") {
        decodeCommand.cmd = "RRF";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new rrf();
    }

    // RLF
    if (this->toDecode.substr(0, 6) == "001101") {
        decodeCommand.cmd = "RLF";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new rlf();
    }

    // XORWF
    if (this->toDecode.substr(0, 6) == "000110") {
        decodeCommand.cmd = "XORWF";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new xorwf();
    }

    // SUBLW
    if (this->toDecode.substr(0, 5) == "11110") {
        decodeCommand.cmd = "SUBLW";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = stoi(this->toDecode.substr(6, 8), nullptr, 2);
        decodeCommand.cmdobject = new sublw();
    }

    // ADDLW
    if (this->toDecode.substr(0, 5) == "11111") {
        decodeCommand.cmd = "ADDLW";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = stoi(this->toDecode.substr(6, 8), nullptr, 2);
        decodeCommand.cmdobject = new addlw();
    }

    // BTFSC
    if (this->toDecode.substr(0, 4) == "0110") {
        decodeCommand.cmd = "BTFSC";
        decodeCommand.literal = stoi(this->toDecode.substr(4, 3), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.dBit = -1;
        decodeCommand.cmdobject = new btfsc();
    }

    // BTFSS
    if (this->toDecode.substr(0, 4) == "0111") {
        decodeCommand.cmd = "BTFSS";
        decodeCommand.literal = stoi(this->toDecode.substr(4, 3), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.dBit = -1;
        decodeCommand.cmdobject = new btfss();
    }

    // BCF
    if (this->toDecode.substr(0, 4) == "0100") {
        decodeCommand.cmd = "BCF";
        decodeCommand.literal = stoi(this->toDecode.substr(4, 3), nullptr, 2);
        decodeCommand.filepos = (stoi(this->toDecode.substr(7, 7), nullptr, 2));
        decodeCommand.dBit = -1;
        decodeCommand.cmdobject = new bcf();
    }

    // BSF
    if (this->toDecode.substr(0, 4) == "0101") {
        decodeCommand.cmd = "BSF";
        decodeCommand.literal = stoi(this->toDecode.substr(4, 3), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.dBit = -1;
        decodeCommand.cmdobject = new bsf();
    }

    // RETLW
    if (this->toDecode.substr(0, 4) == "1101") {
        decodeCommand.cmd = "RETLW";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = stoi(this->toDecode.substr(6, 8), nullptr, 2);
        decodeCommand.cmdobject = new retlw();
    }

    // MOVLW
    if (this->toDecode.substr(0, 4) == "1100") {
        decodeCommand.cmd = "MOVLW";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = stoi(this->toDecode.substr(6, 8), nullptr, 2);
        decodeCommand.cmdobject = new movlw();
    }

    // CALL
    if (this->toDecode.substr(0, 3) == "100") {
        decodeCommand.cmd = "CALL";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = stoi(this->toDecode.substr(3, 11), nullptr, 2);
        decodeCommand.cmdobject = new cmdcall();
    }

    // GOTO
    if (this->toDecode.substr(0, 3) == "101") {
        decodeCommand.cmd = "GOTO";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = stoi(this->toDecode.substr(3, 11), nullptr, 2);
        decodeCommand.cmdobject = new cmdgo();
    }
    return decodeCommand;
}



