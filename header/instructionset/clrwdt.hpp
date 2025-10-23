#pragma once

#include "../instruction.hpp"

class CLRWDT: public Instruction 
{
 public:
 void execute(); 
};
