#include "iorlw.hpp"

IORLW::IORLW(uint16_t instruction) {
    literal = instruction & 0xFF;
}

uint16_t IORLW::execute()
{
return 0;
}
