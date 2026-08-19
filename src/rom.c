
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "rom.h"
#include "memory.h"



uint8_t* load_rom(char* filename) {

    // OPEN THE ROM
    FILE *rom_file = fopen(filename, "rb");
    if (rom_file == NULL) {
        printf("Failed to open ROM: %s\n", filename);
        return NULL;
    }

    fseek(rom_file, 0, SEEK_END);
    long size = ftell(rom_file);
    fseek(rom_file, 0, SEEK_SET);


    // PARSE HEADER
    uint8_t header[0x180];
    char name[17];
	int rom_type;
	int rom_size;
	int ram_size;

    // Read in header
    fread(header, 0x180, 1, rom_file);

    // Read in name
    memset(name, '\0', 17);
    for(int i = 0; i < 15; i++) {
        name[i] = header[i + ROM_NAME_OFFSET];
    }
    name[15] = '\0'; // ensure null-terminated even if title used all 15 bytes
    uint8_t cgbFlag = header[ROM_NAME_OFFSET + 15]; // 0x143, (not needed in basic implementation)
    printf("ROM Name: %s", name);


    

    uint8_t* buffer = malloc(size);

    fread(buffer, 1, size, rom_file);
    fclose(rom_file);

    return buffer;
}