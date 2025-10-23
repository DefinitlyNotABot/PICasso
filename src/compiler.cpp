#include "../header/compiler.hpp"
#include "../header/instructionset/addwf.hpp"
#include "../header/instructionset/andwf.hpp"
#include "../header/instructionset/clrf.hpp"
#include "../header/instructionset/clrw.hpp"
#include "../header/instructionset/comf.hpp"
#include "../header/instructionset/decf.hpp"
#include "../header/instructionset/decfsz.hpp"
#include "../header/instructionset/incf.hpp"
#include "../header/instructionset/incfsz.hpp"
#include "../header/instructionset/iorwf.hpp"
#include "../header/instructionset/movf.hpp"
#include "../header/instructionset/movwf.hpp"
#include "../header/instructionset/nop.hpp"
#include "../header/instructionset/rlf.hpp"
#include "../header/instructionset/rrf.hpp"
#include "../header/instructionset/subwf.hpp"
#include "../header/instructionset/swapf.hpp"
#include "../header/instructionset/xorwf.hpp"
#include "../header/instructionset/bcf.hpp"
#include "../header/instructionset/bsf.hpp"
#include "../header/instructionset/btfsc.hpp"
#include "../header/instructionset/btfss.hpp"
#include "../header/instructionset/addlw.hpp"
#include "../header/instructionset/andlw.hpp"
#include "../header/instructionset/call.hpp"
#include "../header/instructionset/clrwdt.hpp"
#include "../header/instructionset/goto.hpp"
#include "../header/instructionset/iorlw.hpp"
#include "../header/instructionset/movlw.hpp"
#include "../header/instructionset/retfie.hpp"
#include "../header/instructionset/retlw.hpp"
#include "../header/instructionset/return.hpp"
#include "../header/instructionset/sleep.hpp"
#include "../header/instructionset/sublw.hpp"
#include "../header/instructionset/xorlw.hpp"
#include <vector>

std::tuple<bool, std::vector<Instruction*>> Compiler::compileSourcecode(std::string code)
{

    std::vector<Instruction*> compilationOutput(1024, nullptr);




    return {false, {}};
}


Instruction* getInstruction(const uint16_t instruction)
{
    
    uint16_t bitmap7bit = 0b0011111110000000;
    uint16_t bitmap6bit = 0b0011111100000000;
    uint16_t bitmap5bit = 0b0011111000000000;
    uint16_t bitmap4bit = 0b0011110000000000;
    uint16_t bitmap3bit = 0b0011100000000000;

    uint16_t instructionMapped;

    switch(instruction)
    {
        case 0x0064: // CLRWDT            
            return new CLRWDT();
        case 0x0009: // RETFIE
            return new RETFIE();
        case 0x0008: // RETURN
            return new RETURN();
        case 0x0063: // SLEEP
            return new SLEEP();
        default:
            break;
    }

    instructionMapped = instruction & bitmap7bit;

    switch (instructionMapped)
    {
    case 0x0180: // CLRF
        return new CLRF(instruction & 0b01111111);
    case 0x0100: // CLRW
        return new CLRW();
    case 0x0080: // MOVWF
        return new MOVWF(instruction & 0b01111111);
    case 0x0000: // NOP
        return new NOP();
    default:
        break;
    }


    instructionMapped = instruction & bitmap6bit;
    switch (instructionMapped)
    {
    case 0x0700: // ADDWF
        return new ADDWF(instruction & 0b10000000, instruction & 0b01111111);
    case 0x0500: // ANDWF        
        return new ANDWF(instruction & 0b10000000, instruction & 0b01111111);
    case 0x0900: // COMF        
        return new COMF(instruction & 0b10000000, instruction & 0b01111111);
    case 0x0300: // DECF
        return new DECF(instruction & 0b10000000, instruction & 0b01111111);
    case 0x0B00: // DECFSZ
        return new DECFSZ(instruction & 0b10000000, instruction & 0b01111111);
    case 0x0A00: // INCF
        return new INCF(instruction & 0b10000000, instruction & 0b01111111);
    case 0x0F00: // INCFSZ
        return new INCFSZ(instruction & 0b10000000, instruction & 0b01111111);
    case 0x0400: // IORWF
        return new IORWF(instruction & 0b10000000, instruction & 0b01111111);
    case 0x0800: // MOVF
        return new MOVF(instruction & 0b10000000, instruction & 0b01111111);
    case 0x0D00: // RLF
        return new RLF(instruction & 0b10000000, instruction & 0b01111111);
    case 0x0C00: // RRF
        return new RRF(instruction & 0b10000000, instruction & 0b01111111);
    case 0x0200: // SUBWF
        return new SUBWF(instruction & 0b10000000, instruction & 0b01111111);
    case 0x0E00: // SWAPF
        return new SWAPF(instruction & 0b10000000, instruction & 0b01111111);
    case 0x0600: // XORWF
        return new XORWF(instruction & 0b10000000, instruction & 0b01111111);
    case 0x3900: // ANDLW        
        return new ANDLW(instruction & 0xFF);
    case 0x3800: // IORLW
        return new IORLW(instruction & 0xFF);
    case 0x3A00: // XORLW
        return new XORLW(instruction & 0xFF);
    default:
        break;
    }
    instructionMapped = instruction & bitmap5bit;
    switch (instructionMapped)
    {
        case 0x3E00: // ADDLW
            return new ADDLW(instruction & 0xFF);
        case 0x3C00: // SUBLW
            return new SUBLW(instruction & 0xFF);
        default:
            break;
    }
    instructionMapped = instruction & bitmap4bit;
    switch (instructionMapped)
    {
        case 0x1000: // BCF            
            return new BCF(instruction & 0b1110000000, instruction & 0b0001111111);
        case 0x1400: // BSF
            return new BSF(instruction & 0b1110000000, instruction & 0b0001111111);
        case 0x1800: // BTFSC
            return new BTFSC(instruction & 0b1110000000, instruction & 0b0001111111);
        case 0x1C00: // BTFSS
            return new BTFSS(instruction & 0b1110000000, instruction & 0b0001111111);
        case 0x3000: // MOVLW
            return new MOVLW(instruction & 0xFF);
        case 0x3400: // RETLW
            return new RETLW(instruction & 0xFF);
        default:
            break;
    }
    instructionMapped = instruction & bitmap3bit;

    switch (instructionMapped)
    {
        case 0x2000: // CALL
            return new CALL(instruction & 0x7FF);
        case 0x2800: // GOTO
            return new GOTO(instruction & 0x7FF);
        default:
            break;
    }

    return nullptr;
}
