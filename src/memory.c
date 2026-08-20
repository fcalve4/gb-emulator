#include "memory.h"


uint8_t cart[0x8000];
uint8_t vram[0x2000];
uint8_t sram[0x2000];
uint8_t wram[0x2000];
uint8_t oam[0x100];
uint8_t hram[0x80];
uint8_t io[0x100];


// Read byte from 16-bit address
uint8_t read_byte(uint16_t address) {
    if (address <= 0x7fff) {
		return cart[address];
    }
    else if (address >= 0x8000 && address <= 0x9fff) {
		return vram[address - 0x8000];
    }
    else if (address >= 0xa000 && address <= 0xbfff) {
		return sram[address - 0xa000];
    }
	else if (address >= 0xc000 && address <= 0xdfff) {
		return wram[address - 0xc000];
    }
	else if (address >= 0xe000 && address <= 0xfdff) {
		return wram[address - 0xe000];
    }
	else if (address >= 0xfe00 && address <= 0xfe9f) {
		return oam[address - 0xfe00];
    }
    return 0;
}

// Write byte to 16-bit address
void write_byte(uint16_t address, uint8_t value) {
    if (address <= 0x7fff) {
        // writes to ROM are ignored on ROM-only carts (no mappers yet)
        return;
    }
    else if (address >= 0x8000 && address <= 0x9fff) {
        vram[address - 0x8000] = value;
    }
    else if (address >= 0xa000 && address <= 0xbfff) {
        sram[address - 0xa000] = value;
    }
    else if (address >= 0xc000 && address <= 0xdfff) {
        wram[address - 0xc000] = value;
    }
    else if (address >= 0xe000 && address <= 0xfdff) {
        wram[address - 0xe000] = value;
    }
    else if (address >= 0xfe00 && address <= 0xfe9f) {
        oam[address - 0xfe00] = value;
    }
    else if (address >= 0xff00 && address <= 0xff7f) {
        io[address - 0xff00] = value;
    }
    else if (address >= 0xff80 && address <= 0xfffe) {
        hram[address - 0xff80] = value;
    }
}

uint16_t read_short(uint16_t address) {
	return read_byte(address) | (read_byte(address + 1) << 8);
}

void write_short(uint16_t address, uint16_t value) {
	write_byte(address, (uint8_t)(value & 0x00ff));
	write_byte(address + 1, (uint8_t)((value & 0xff00) >> 8));
}