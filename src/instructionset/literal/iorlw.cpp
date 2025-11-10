#include "iorlw.hpp"

IORLW::IORLW(uint16_t instruction) {
    literal = instruction & 0xFF;
}

uint16_t IORLW::execute()
{
return 0;
}
// Implementation of the instruction name getter
std::string IORLW::getName()
{
    return "iorlw";
}

