#pragma once

#include <cstdint>

class Bus;

class CPU6502 {
public:
    CPU6502();
    ~CPU6502();
    void connectBus(Bus *b)
    {
        bus = b;
    }
    enum FLAGS6502{
        C = (1 << 0), // Carry bit
        Z = (1 << 1), // Set if A = 0
        I = (1 << 2), // Interrupt Disable
        D = (1 << 3), // Decimal mode
        B = (1 << 4), // Break
        U = (1 << 5), // Unsued
        V = (1 << 6), // Overflow
        N = (1 << 7), // negative
    };
    uint8_t a = 0x00; // Accumulator register
    uint8_t x = 0x00;
    uint8_t y = 0x00;
    uint16_t pc = 0x0000; // Program counter
    uint16_t sp = 0x00; // Stack pointer
    uint8_t status = 0x00; // Status register
private:
    Bus *bus = nullptr;
    uint8_t read(uint16_t a);
    void write(uint16_t a, uint8_t d);
};

