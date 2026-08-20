#include <string.h>

#include "cpu.h"
#include "memory.h"
#include "registers.h"

#include <stdint.h>

// Number of operand bytes following each opcode (0, 1, or 2)
const uint8_t operand_lengths[256] = {
    0, 2, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 1, 0,
    1, 2, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0,
    1, 2, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0,
    1, 2, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 2, 2, 2, 0, 1, 0, 0, 0, 2, 1, 2, 2, 1, 0,
    0, 0, 2, 0, 2, 0, 1, 0, 0, 0, 2, 0, 2, 0, 1, 0,
    1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 2, 0, 0, 0, 1, 0,
    1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 2, 0, 0, 0, 1, 0,
};

void init() {
   	memset(sram, 0, sizeof(sram));
	memset(io, 0, sizeof(io));
	memset(vram, 0, sizeof(vram));
	memset(oam, 0, sizeof(oam));
	memset(wram, 0, sizeof(wram));
	memset(hram, 0, sizeof(hram));

    registers.a = 0x01;
    registers.f = 0xb0;
    registers.b = 0x00;
    registers.c = 0x13;
    registers.d = 0x00;
    registers.e = 0xd8;
    registers.h = 0x01;
    registers.l = 0x4d;

    registers.sp = 0xfffe;
    registers.pc = 0x100;
}
/**
 * Returns # of cycles 
 */
int step() {
	uint8_t instruction;
	uint16_t operand = 0;

    // Grab instruction at pc and then advance pc
    instruction = read_byte(registers.pc);
    registers.pc++;

    // Get operand using operand length table
    uint8_t operand_length = operand_lengths[instruction];
    if (operand_length == 1) {
        operand = read_byte(registers.pc);
    }
    else if (operand_length == 2) {
        operand = read_byte(registers.pc) | (read_byte(registers.pc + 1) << 8);
    }
    registers.pc += operand_length; // Advance PC to next operand

    switch (instruction) {
        case 0x00: // NOP
            return 1;
        case 0x01: // LD bc, u16
            registers.bc = operand;
            return 3;
        default:
            fprintf(stderr, "Unimplemented instruction: 0x%02X at 0x%04X\n", instruction, registers.pc - 1);
            exit(1);
    }
    
}