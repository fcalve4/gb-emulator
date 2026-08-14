#include "memory.h"


uint8_t memory[0x10000]; // 64KB address space

void load_into_memory(uint8_t* rom_buffer, long rom_size) {
    // simplest case: ROM <= 32KB, no bank switching needed yet
    for (long i = 0; i < rom_size && i < 0x8000; i++) {
        memory[i] = rom_buffer[i];
    }
}