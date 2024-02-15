#pragma once

#include <cstdint>
#include <string>
#include <vector>

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
    uint8_t opcode = 0x00; // Opcode
    uint8_t cycles = 0;
    uint8_t fetched = 0x00;
    uint16_t addr_abs = 0x0000;
    uint16_t addr_rel = 0x00;

    void clock(); // Clock signal
    void reset(); // Reset Signal
    void irq(); // Interrupt Request
    void nmi(); // Non maskable interrupt request
    uint8_t fetch();

    // Addressing Modes

    /*
     * Implicit
     For many 6502 instructions the source and destination of the information to be manipulated is implied directly
     by the function of the instruction itself and no further operand needs to be specified.
     Operations like 'Clear Carry Flag' (CLC) and 'Return from Subroutine' (RTS) are implicit.
     */
    uint8_t IMP();

    /*
     * Immediate
     * Immediate addressing allows the programmer to directly specify an 8 bit constant within the instruction.
     * It is indicated by a '#' symbol followed by an numeric expression.
     */
    uint8_t IMM();
    /*
    * Zero Page
    * An instruction using zero page addressing mode has only an 8 bit address operand.
    * This limits it to addressing only the first 256 bytes of memory (e.g. $0000 to $00FF) where the most significant
    * byte of the address is always zero. In zero page mode only the least significant byte of the address is held in
    * the instruction making it shorter by one byte (important for space saving) and one less memory fetch during
    * execution (important for speed).
     */
    uint8_t ZP0();

    /* Zero Page, X
     * The address to be accessed by an instruction using indexed zero page addressing is calculated by taking the
     * 8 bit zero page address from the instruction and adding the current value of the X register to it.
     * For example if the X register contains $0F and the instruction LDA $80,X is executed then the accumulator will
     * be loaded from $008F (e.g. $80 + $0F => $8F).
     */
    uint8_t ZPX();

    /* Zero Page, Y
     * The address to be accessed by an instruction using indexed zero page addressing is calculated by taking the
     * 8 bit zero page address from the instruction and adding the current value of the Y register to it.
     * This mode can only be used with the LDX and STX instructions.
     */
    uint8_t ZPY();

    /* Relative
     * Relative addressing mode is used by branch instructions (e.g. BEQ, BNE, etc.) which contain a signed 8 bit
     * relative offset (e.g. -128 to +127) which is added to program counter if the condition is true. As the program
     * counter itself is incremented during instruction execution by two the effective address range for the target
     * instruction must be with -126 to +129 bytes of the branch.
     */
    uint8_t REL();

    /*
     * Absolute
     * Instructions using absolute addressing contain a full 16 bit address to identify the target location.
     */
    uint8_t ABS();

    /* Absolute, X
     * The address to be accessed by an instruction using X register indexed absolute addressing is computed by taking
     * the 16 bit address from the instruction and added the contents of the X register. For example if X contains $92
     * then an STA $2000,X instruction will store the accumulator at $2092 (e.g. $2000 + $92).
     */
    uint8_t ABX();

    /*
     * Absolute, Y
     * The Y register indexed absolute addressing mode is the same as the previous mode only with the contents of the
     * Y register added to the 16 bit address from the instruction.
     */
    uint8_t ABY();

    /*
     * JMP is the only 6502 instruction to support indirection. The instruction contains a 16 bit address which
     * identifies the location of the least significant byte of another 16 bit memory address which is the real
     * target of the instruction.
     * For example if location $0120 contains $FC and location $0121 contains $BA then the instruction JMP ($0120)
     * will cause the next instruction execution to occur at $BAFC (e.g. the contents of $0120 and $0121).
     */
    uint8_t IND();

    /*
     * Indexed Indirect
     * Indexed indirect addressing is normally used in conjunction with a table of address held on zero page.
     * The address of the table is taken from the instruction and the X register added to it (with zero page wrap around)
     * to give the location of the least significant byte of the target address.
     */
    uint8_t IZX();

    /*
     * Indirect Indexed
     * Indirect indirect addressing is the most common indirection mode used on the 6502. In instruction contains the
     * zero page location of the least significant byte of 16 bit address. The Y register is dynamically added to this
     * value to generated the actual target address for operation.
     */
    uint8_t IZY();

    // OPCODES - There are 56 of them "official opcodes"
    uint8_t ADC();	uint8_t AND();	uint8_t ASL();	uint8_t BCC();
    uint8_t BCS();	uint8_t BEQ();	uint8_t BIT();	uint8_t BMI();
    uint8_t BNE();	uint8_t BPL();	uint8_t BRK();	uint8_t BVC();
    uint8_t BVS();	uint8_t CLC();	uint8_t CLD();	uint8_t CLI();
    uint8_t CLV();	uint8_t CMP();	uint8_t CPX();	uint8_t CPY();
    uint8_t DEC();	uint8_t DEX();	uint8_t DEY();	uint8_t EOR();
    uint8_t INC();	uint8_t INX();	uint8_t INY();	uint8_t JMP();
    uint8_t JSR();	uint8_t LDA();	uint8_t LDX();	uint8_t LDY();
    uint8_t LSR();	uint8_t NOP();	uint8_t ORA();	uint8_t PHA();
    uint8_t PHP();	uint8_t PLA();	uint8_t PLP();	uint8_t ROL();
    uint8_t ROR();	uint8_t RTI();	uint8_t RTS();	uint8_t SBC();
    uint8_t SEC();	uint8_t SED();	uint8_t SEI();	uint8_t STA();
    uint8_t STX();	uint8_t STY();	uint8_t TAX();	uint8_t TAY();
    uint8_t TSX();	uint8_t TXA();	uint8_t TXS();	uint8_t TYA();

    // Catch the illegal operations
    uint8_t NNN();

    // This struct contains the information pertaining to a certain instruction
    struct INSTRUCTION
    {
        // English name of instruction
        std::string name;
        // Function pointer to the opcode implementation
        uint8_t (CPU6502::*operate)(void) = nullptr;
        // Function pointer to the addressing mode implementation
        uint8_t (CPU6502::*addrmode)(void) = nullptr;
        // Number representing the number of clock cycles need to complete instruction
        uint8_t cycles = 0;
    };

    // Vector of instructions to allow for fast lookup
    std::vector<INSTRUCTION> LOOKUP;



private:
    Bus *bus = nullptr;
    uint8_t read(uint16_t a);
    void write(uint16_t a, uint8_t d);
};

