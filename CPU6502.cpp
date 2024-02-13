#include "CPU6502.h"

uint8_t CPU6502::read(uint16_t a) {
    return bus->read(a, false);
}

void CPU6502::write(uint16_t a, uint8_t d) {
    bus->write(a, d);
}