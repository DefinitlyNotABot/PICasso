#pragma once

#include "instruction.hpp"


// Arithmetic and logic instructions
class ADDWF : public Instruction 
{
   private:
      uint16_t destination;
      uint16_t file;
   public:
      ADDWF(uint16_t destination, uint16_t file);
 void execute(); 
};

class ANDWF : public Instruction 
{
   private:
      uint16_t destination;
      uint16_t file;
   public:
      ANDWF(uint16_t destination, uint16_t file);
      void execute(); 
};

class CLRF  : public Instruction 
{
    uint16_t file;
 public:
    CLRF(uint16_t file);
 void execute();
};

class CLRW  : public Instruction 
{
 public:
 void execute(); 
};

class COMF  : public Instruction 
{
   private:
      uint16_t destination;
      uint16_t file;
   public:
      COMF(uint16_t destination, uint16_t file);
      void execute(); 
};

class DECF  : public Instruction 
{
   private:
      uint16_t destination;
      uint16_t file;
   public:
      DECF(uint16_t destination, uint16_t file);
      void execute(); 
};

class DECFSZ: public Instruction 
{
   private:
      uint16_t destination;
      uint16_t file;
   public:
      DECFSZ(uint16_t destination, uint16_t file);
 void execute(); 
};

class INCF  : public Instruction 
{
   private:
      uint16_t destination;
      uint16_t file;
   public:
      INCF(uint16_t destination, uint16_t file);
      void execute(); 
};

class INCFSZ  : public Instruction 
{
   private:
      uint16_t destination;
      uint16_t file;
   public:
      INCFSZ(uint16_t destination, uint16_t file);
      void execute(); 
};

class IORWF : public Instruction 
{
   private:
      uint16_t destination;
      uint16_t file;
   public:
   IORWF(uint16_t destination, uint16_t file);
 void execute(); 
};

class MOVF  : public Instruction 
{
    private:
      uint16_t destination;
      uint16_t file;
   public:
   MOVF(uint16_t destination, uint16_t file);
 void execute(); 

};

class MOVWF : public Instruction 
{
    uint16_t file;
 public:
    MOVWF(uint16_t file);
 void execute(); 
};

class NOP   : public Instruction 
{
 public:
 void execute(); 
};

class RLF   : public Instruction 
{
    private:
      uint16_t destination;
      uint16_t file;
   public:
   RLF(uint16_t destination, uint16_t file);
 void execute(); 
};

class RRF   : public Instruction 
{
    private:
      uint16_t destination;
      uint16_t file;
   public:
   RRF(uint16_t destination, uint16_t file);
 void execute(); 
};

class SUBWF : public Instruction 
{
    private:
      uint16_t destination;
      uint16_t file;
   public:
   SUBWF(uint16_t destination, uint16_t file);
 void execute(); 
};

class SWAPF : public Instruction 
{
    private:
      uint16_t destination;
      uint16_t file;
   public:
   SWAPF(uint16_t destination, uint16_t file);
 void execute(); 
};

class XORWF : public Instruction 
{
    private:
      uint16_t destination;
      uint16_t file;
   public:
   XORWF(uint16_t destination, uint16_t file);
 void execute(); 
};


// Bit operations
class BCF   : public Instruction 
{
   uint8_t bit;
   uint16_t file;
 public:
   BCF(uint8_t bit, uint16_t file);
 void execute(); 
};

class BSF   : public Instruction 
{
   uint8_t bit;
   uint16_t file;
 public:
   BSF(uint8_t bit, uint16_t file);
 void execute(); 
};
 // You wrote NSF; assuming BSF (set bit)
class BTFSC : public Instruction 
{
   uint8_t bit;
   uint16_t file;
 public:
   BTFSC(uint8_t bit, uint16_t file);
 void execute(); 
};

class BTFSS : public Instruction 
{
   uint8_t bit;
   uint16_t file;
 public:
   BTFSS(uint8_t bit, uint16_t file);
 void execute(); 
};


// Literal and control instructions
class ADDLW : public Instruction 
{
   private:
      uint16_t literal;
   public:
   ADDLW(uint16_t literal);
 void execute(); 
};

class ANDLW : public Instruction 
{
   private:
      uint16_t literal;
   public:
   ANDLW(uint16_t literal);
 void execute(); 
};

class CALL  : public Instruction 
{
   uint16_t address;
 public:
   CALL(uint16_t address);
 void execute(); 
};

class CLRWDT: public Instruction 
{
 public:
 void execute(); 
};

class GOTO  : public Instruction 
{
   uint16_t address;
 public:
   GOTO(uint16_t address);
 void execute(); 
};

class IORLW : public Instruction 
{
    private:
      uint16_t literal;
   public:
   IORLW(uint16_t literal);
 void execute(); 
};

class MOVLW : public Instruction 
{
   uint16_t file;
 public:
   MOVLW(uint16_t file);
 void execute(); 
};

class RETFIE: public Instruction 
{
 public:
 void execute(); 
};

class RETLW : public Instruction 
{
   uint16_t file;
 public:
   RETLW(uint16_t file);
 void execute(); 
};

class RETURN: public Instruction 
{
 public:
 void execute(); 
};

class SLEEP : public Instruction 
{
 public:
 void execute(); 
};

class SUBLW : public Instruction 
{
   private:
      uint16_t literal;
   public:
   SUBLW(uint16_t literal);
 void execute(); 
};

class XORLW : public Instruction 
{
    private:
      uint16_t literal;
   public:
   XORLW(uint16_t literal);
 void execute(); 
};


