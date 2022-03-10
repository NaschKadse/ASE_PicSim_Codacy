#include "decode.h"
#include "1_Domain_Code/movlw.h"
#include "1_Domain_Code/retfie.h"
#include "1_Domain_Code/cmdreturn.h"
#include "1_Domain_Code/nop.h"
#include "1_Domain_Code/clrf.h"
#include "1_Domain_Code/clrw.h"
#include "1_Domain_Code/movwf.h"
#include "1_Domain_Code/subwf.h"
#include "1_Domain_Code/iorwf.h"
#include "1_Domain_Code/movf.h"
#include "1_Domain_Code/swapf.h"
#include "1_Domain_Code/addwf.h"
#include "1_Domain_Code/andwf.h"
#include "1_Domain_Code/andlw.h"
#include "1_Domain_Code/decfsz.h"
#include "1_Domain_Code/incfsz.h"
#include "1_Domain_Code/comf.h"
#include "1_Domain_Code/iorlw.h"
#include "1_Domain_Code/decf.h"
#include "1_Domain_Code/incf.h"
#include "1_Domain_Code/xorlw.h"
#include "1_Domain_Code/rrf.h"
#include "1_Domain_Code/rlf.h"
#include "1_Domain_Code/xorwf.h"
#include "1_Domain_Code/sublw.h"
#include "1_Domain_Code/addlw.h"
#include "1_Domain_Code/btfsc.h"
#include "1_Domain_Code/btfss.h"
#include "1_Domain_Code/bcf.h"
#include "1_Domain_Code/bsf.h"
#include "1_Domain_Code/retlw.h"
#include "1_Domain_Code/cmdcall.h"
#include "1_Domain_Code/cmdgo.h"

decode::decode(std::string inputCmd) {
    this->toDecode = std::move(inputCmd);
}
decode::~decode() = default;
decode::decodedCmd decode::decodeCommand() {
    decodedCmd decodeCommand;


    // RETFIE
    if (this->toDecode.substr(0, 14) == "00000000001001") {
        decodeCommand.cmd = "double";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new retfie();
    }

    // RETURN
    if (this->toDecode.substr(0, 14) == "00000000001000") {
        decodeCommand.cmd = "double";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new cmdreturn();
    }

    // NOP
    if (this->toDecode.substr(0, 7) == "0000000" && this->toDecode.substr(9, 5) == "00000") {
        decodeCommand.cmd = "normal";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new nop();
    }

    // CLRF
    if (this->toDecode.substr(0, 7) == "0000011") {
        decodeCommand.cmd = "normal";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new clrf();
    }

    // CLRW
    if (this->toDecode.substr(0, 7) == "0000010") {
        decodeCommand.cmd = "normal";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new clrw();
    }

    // MOVWF
    if (this->toDecode.substr(0, 7) == "0000001") {
        decodeCommand.cmd = "normal";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new movwf();
    }

    //SUBWF
    if (this->toDecode.substr(0, 6) == "000010") {
        decodeCommand.cmd = "normal";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new subwf();
    }

    // IORWF
    if (this->toDecode.substr(0, 6) == "000100") {
        decodeCommand.cmd = "normal";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new iorwf();
    }

    // MOVF
    if (this->toDecode.substr(0, 6) == "001000") {
        decodeCommand.cmd = "normal";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new movf();
    }

    // SWAPF
    if (this->toDecode.substr(0, 6) == "001110") {
        decodeCommand.cmd = "normal";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new swapf();
    }

    // ADDWF
    if (this->toDecode.substr(0, 6) == "000111") {
        decodeCommand.cmd = "normal";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new addwf() ;

    }

    // ANDWF
    if (this->toDecode.substr(0, 6) == "000101") {
        decodeCommand.cmd = "normal";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new andwf();
    }

    // ANDLW
    if (this->toDecode.substr(0, 6) == "111001") {
        decodeCommand.cmd = "normal";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = stoi(this->toDecode.substr(6, 8), nullptr, 2);
        decodeCommand.cmdobject = new andlw();
    }

    // DECFSZ
    if (this->toDecode.substr(0, 6) == "001011") {
        decodeCommand.cmd = "normal";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new decfsz();
    }

    // INCFSZ
    if (this->toDecode.substr(0, 6) == "001111") {
        decodeCommand.cmd = "normal";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new incfsz();
    }

    // COMF
    if (this->toDecode.substr(0, 6) == "001001") {
        decodeCommand.cmd = "normal";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new comf();
    }

    // IORLW
    if (this->toDecode.substr(0, 6) == "111000") {
        decodeCommand.cmd = "normal";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = stoi(this->toDecode.substr(6, 9), nullptr, 2);
        decodeCommand.cmdobject = new iorlw();
    }

    // DECF
    if (this->toDecode.substr(0, 6) == "000011") {
        decodeCommand.cmd = "normal";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new decf();
    }

    // INCF
    if (this->toDecode.substr(0, 6) == "001010") {
        decodeCommand.cmd = "normal";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new incf();
    }

    // XORLW
    if (this->toDecode.substr(0, 6) == "111010") {
        decodeCommand.cmd = "normal";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = stoi(this->toDecode.substr(6, 8), nullptr, 2);
        decodeCommand.cmdobject = new xorlw();
    }

    // RRF
    if (this->toDecode.substr(0, 6) == "001100") {
        decodeCommand.cmd = "normal";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new rrf();
    }

    // RLF
    if (this->toDecode.substr(0, 6) == "001101") {
        decodeCommand.cmd = "normal";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new rlf();
    }

    // XORWF
    if (this->toDecode.substr(0, 6) == "000110") {
        decodeCommand.cmd = "normal";
        decodeCommand.dBit = stoi(this->toDecode.substr(6, 1), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.literal = -1;
        decodeCommand.cmdobject = new xorwf();
    }

    // SUBLW
    if (this->toDecode.substr(0, 5) == "11110") {
        decodeCommand.cmd = "normal";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = stoi(this->toDecode.substr(6, 8), nullptr, 2);
        decodeCommand.cmdobject = new sublw();
    }

    // ADDLW
    if (this->toDecode.substr(0, 5) == "11111") {
        decodeCommand.cmd = "normal";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = stoi(this->toDecode.substr(6, 8), nullptr, 2);
        decodeCommand.cmdobject = new addlw();
    }

    // BTFSC
    if (this->toDecode.substr(0, 4) == "0110") {
        decodeCommand.cmd = "normal";
        decodeCommand.literal = stoi(this->toDecode.substr(4, 3), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.dBit = -1;
        decodeCommand.cmdobject = new btfsc();
    }

    // BTFSS
    if (this->toDecode.substr(0, 4) == "0111") {
        decodeCommand.cmd = "normal";
        decodeCommand.literal = stoi(this->toDecode.substr(4, 3), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.dBit = -1;
        decodeCommand.cmdobject = new btfss();
    }

    // BCF
    if (this->toDecode.substr(0, 4) == "0100") {
        decodeCommand.cmd = "normal";
        decodeCommand.literal = stoi(this->toDecode.substr(4, 3), nullptr, 2);
        decodeCommand.filepos = (stoi(this->toDecode.substr(7, 7), nullptr, 2));
        decodeCommand.dBit = -1;
        decodeCommand.cmdobject = new bcf();
    }

    // BSF
    if (this->toDecode.substr(0, 4) == "0101") {
        decodeCommand.cmd = "normal";
        decodeCommand.literal = stoi(this->toDecode.substr(4, 3), nullptr, 2);
        decodeCommand.filepos = stoi(this->toDecode.substr(7, 7), nullptr, 2);
        decodeCommand.dBit = -1;
        decodeCommand.cmdobject = new bsf();
    }

    // RETLW
    if (this->toDecode.substr(0, 4) == "1101") {
        decodeCommand.cmd = "double";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = stoi(this->toDecode.substr(6, 8), nullptr, 2);
        decodeCommand.cmdobject = new retlw();
    }

    // MOVLW
    if (this->toDecode.substr(0, 4) == "1100") {
        decodeCommand.cmd = "normal";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = stoi(this->toDecode.substr(6, 8), nullptr, 2);
        decodeCommand.cmdobject = new movlw();
    }

    // CALL
    if (this->toDecode.substr(0, 3) == "100") {
        decodeCommand.cmd = "double";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = stoi(this->toDecode.substr(3, 11), nullptr, 2);
        decodeCommand.cmdobject = new cmdcall();
    }

    // GOTO
    if (this->toDecode.substr(0, 3) == "101") {
        decodeCommand.cmd = "double";
        decodeCommand.dBit = -1;
        decodeCommand.filepos = -1;
        decodeCommand.literal = stoi(this->toDecode.substr(3, 11), nullptr, 2);
        decodeCommand.cmdobject = new cmdgo();
    }
    return decodeCommand;
}



