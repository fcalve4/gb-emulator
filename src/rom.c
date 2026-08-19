
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "rom.h"

uint8_t* load_rom(char* filename, long* rom_size) {
    
    FILE *rom = fopen(filename, "rb");
    if (rom == NULL) {
        printf("Failed to open ROM: %s\n", filename);
        return NULL;
    }

    fseek(rom, 0, SEEK_END);
    long size = ftell(rom);
    fseek(rom, 0, SEEK_SET);

    uint8_t* buffer = malloc(size);

    fread(buffer, 1, size, rom);
    fclose(rom);

    *rom_size = size;
    return buffer;
}