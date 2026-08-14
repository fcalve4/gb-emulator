// rom.c

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "rom.h"

uint8_t* load_rom(char* filename) {
    FILE *rom = fopen(filename, "rb");
    if (rom == NULL) {
        printf("Failed to open ROM: %s\n", filename);
        return NULL;
    }

    fseek(rom, 0, SEEK_END);
    long rom_size = ftell(rom);
    fseek(rom, 0, SEEK_SET);

    uint8_t* buffer = malloc(rom_size);

    fread(buffer, 1, rom_size, rom);
    fclose(rom);

    return buffer;
}