#include "addlw.hpp"

ADDLW::ADDLW(uint16_t instruction) {
    literal = instruction & 0xFF;
}

uint16_t ADDLW::execute()
{
return 0;
}
