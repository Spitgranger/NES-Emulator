#pragma once

#include <cstdint>
#include "CPU6502.h"
class Bus {
public:
    Bus();
    ~Bus();
    void write(uint16_t addr, uint8_t data);
    uint8_t read(uint16_t addr, bool bReadOnly = false);
public:
    CPU6502 cpu;
    uint8_t ram[64*1024];
};

