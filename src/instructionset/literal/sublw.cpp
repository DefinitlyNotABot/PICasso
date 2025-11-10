#include "sublw.hpp"

SUBLW::SUBLW(uint16_t instruction) {
    literal = instruction & 0xFF;
}

uint16_t SUBLW::execute()
{
return 0;
}
// Implementation of the instruction name getter
std::string SUBLW::getName()
{
    return "sublw";
}

