#include "alu.hpp"
#include "arithmetic.hpp"
#include "bitwise.hpp"
#include "jump.hpp"
#include "literal.hpp"
#include "ret.hpp"
#include <iostream>
#include <string>

uint16_t ALU::executeInstruction(Instruction& instruction)
{
    uint16_t executionReturn = instruction.execute();
    return executionReturn;
}