#pragma once

#include <stdint.h>

extern uint8_t cart[0x8000];
extern uint8_t sram[0x2000];
extern uint8_t io[0x100];
extern uint8_t vram[0x2000];
extern uint8_t oam[0x100];
extern uint8_t wram[0x2000];
extern uint8_t hram[0x80];