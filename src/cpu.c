#include <string.h>

#include "cpu.h"
#include "memory.h"
#include "registers.h"

#include <stdint.h>

#define FLAG_Z 0b10000000
#define FLAG_N 0b01000000
#define FLAG_H 0b00100000
#define FLAG_C 0b00010000


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

void set_flag(uint8_t flag) {
    registers.f |= flag;
}
void clear_flag(uint8_t flag) {
    registers.f &= ~flag;
}
int is_flag_set(uint8_t flag) {
    return (registers.f & flag) != 0;
}

/**
 * 8bit INC
 */
uint8_t inc8(uint8_t value) {
    // Set Half Carry if low nybble overflows
    if ((value & 0x0F) == 0x0F) { 
        set_flag(FLAG_H);
    }
    else { 
        clear_flag(FLAG_H);
    }

    value += 1;

    if (value == 0) { 
        set_flag(FLAG_Z); 
    }
    else {
        clear_flag(FLAG_Z);
    }

    clear_flag(FLAG_N);
    // C untouched

    return value;
}

uint8_t dec8(uint8_t value) {
    // Set Half Carry if low nybble overflows
    if ((value & 0x0F)) { 
        set_flag(FLAG_H);
    }
    else { 
        clear_flag(FLAG_H);
    }

    value += 1;

    if (value == 0) { 
        set_flag(FLAG_Z); 
    }
    else {
        clear_flag(FLAG_Z);
    }

    clear_flag(FLAG_N);
    // C untouched

    return value;
}


/**
 * Returns # of M-cycles 
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
        case 0x01: // LD BC, n16
            registers.bc = operand;
            return 3;
        case 0x02: // LD [BC], A
            write_byte(registers.bc, registers.a);
            return 2;
        case 0x03: // INC BC
            registers.bc++;
            return 2;
        case 0x04: // INC B
            registers.b = inc8(registers.b);
            return 1;
        case 0x05: // DEC B
            return 1;
        case 0x06: // LD B, n8
            registers.b = operand;
            return 2;
        case 0x07: // RLCA
            return 1;
        case 0x08: // LD [a16], SP
            write_byte(operand, registers.sp & 0xFF);        // low byte of SP -> n16
            write_byte(operand + 1, (registers.sp >> 8) & 0xFF); // high byte of SP -> n16 + 1
            return 5;
        default:
            fprintf(stderr, "Unimplemented instruction: 0x%02X at 0x%04X\n", instruction, registers.pc - 1);
            exit(1);
    }
    
}