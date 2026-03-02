#pragma once

#include "instruction.hpp"
#include "timer.hpp"

class Jump  : public virtual Instruction 
{
    friend class PIC;
    protected:
        uint16_t address;
        static std::shared_ptr<Timer> timer;
    public:

};
