#pragma once

#include "instruction.hpp"


// Arithmetic and logic instructions
class ADDWF : public Instruction { public: void execute(); };
class ANDWF : public Instruction { public: void execute(); };
class CLRF  : public Instruction { public: void execute(); };
class CLRW  : public Instruction { public: void execute(); };
class COMF  : public Instruction { public: void execute(); };
class DECF  : public Instruction { public: void execute(); };
class DECFSZ: public Instruction { public: void execute(); };
class INCF  : public Instruction { public: void execute(); };
class IORWF : public Instruction { public: void execute(); };
class MOVF  : public Instruction { public: void execute(); };
class MOVWF : public Instruction { public: void execute(); };
class NOP   : public Instruction { public: void execute(); };
class RLF   : public Instruction { public: void execute(); };
class RRF   : public Instruction { public: void execute(); };
class SUBWF : public Instruction { public: void execute(); };
class SWAPF : public Instruction { public: void execute(); };
class XORWF : public Instruction { public: void execute(); };

// Bit operations
class BCF   : public Instruction { public: void execute(); };
class BSF   : public Instruction { public: void execute(); }; // You wrote NSF; assuming BSF (set bit)
class BTFSC : public Instruction { public: void execute(); };
class BTFSS : public Instruction { public: void execute(); };

// Literal and control instructions
class ADDLW : public Instruction { public: void execute(); };
class ANDLW : public Instruction { public: void execute(); };
class CALL  : public Instruction { public: void execute(); };
class CLRWDT: public Instruction { public: void execute(); };
class GOTO  : public Instruction { public: void execute(); };
class IORLW : public Instruction { public: void execute(); };
class MOVLW : public Instruction { public: void execute(); };
class RETFIE: public Instruction { public: void execute(); };
class RETLW : public Instruction { public: void execute(); };
class RETURN: public Instruction { public: void execute(); };
class SLEEP : public Instruction { public: void execute(); };
class SUBLW : public Instruction { public: void execute(); };
class XORLW : public Instruction { public: void execute(); };

