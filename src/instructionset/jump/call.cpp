#include "call.hpp"

CALL::CALL(uint16_t instruction) {
    address = instruction & 0x7FF;
}

uint16_t CALL::execute()
{
return 0;
}
// Implementation of the instruction name getter
std::string CALL::getName()
{
    return "call";
}

