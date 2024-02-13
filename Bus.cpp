
#include "Bus.h"
#include <cstring>

Bus::Bus() {
    // Set memory to 0 on initialization
    memset(ram, 0, sizeof(ram));
    cpu.connectBus(this);
}

void Bus::write(uint16_t addr, uint8_t data) {
    if (addr >= 0x0000 && addr <= 0xFFFF)
        ram[addr] = data;

}

uint8_t Bus::read(uint16_t addr, bool bReadOnly) {
    if (addr >= 0x0000 && addr <= 0xFFFF)
        return ram[addr];
    return 0;
}