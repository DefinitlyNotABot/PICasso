#pragma once
#include "memoryInterface.hpp"
#include <memory>

#define INTCON_REGISTER 0x0B
#define RBIF_BIT 0x0
#define INTF_BIT 0x1
#define T0IF_BIT 0x2
#define RBIE_BIT 0x3
#define INTE_BIT 0x4
#define T0IE_BIT 0x5
#define EEIE_BIT 0x6
#define GIE_BIT 0x7

class Interrupts
{
private:
    struct InterruptFlags
    {
        uint8_t RBIF : 1;
        uint8_t INTF : 1;
        uint8_t T0IF : 1;
        uint8_t RBIE : 1;
        uint8_t INTE : 1;
        uint8_t T0IE : 1;
        uint8_t EEIE : 1;
        uint8_t GIE : 1;
    } __attribute__((packed));

    InterruptFlags flags;
    std::shared_ptr<MemoryInterface> memoryInterface;
    void checkINTCON();
    void gotInterrupted();

public:
    Interrupts();
    Interrupts(std::shared_ptr<MemoryInterface> memoryInterface);
    ~Interrupts();

    void checkInterrupts();
};
