
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "rom.h"
#include "memory.h"



void load_rom(char* filename) {

    // OPEN THE ROM
    FILE *rom_file = fopen(filename, "rb");
    if (rom_file == NULL) {
        printf("Failed to open ROM: %s\n", filename);
        return;
    }

    fseek(rom_file, 0, SEEK_END);
    long size = ftell(rom_file);
    fseek(rom_file, 0, SEEK_SET);


    // PARSE HEADER
    uint8_t header[0x180];
    char name[17];
	uint8_t rom_type;
	uint8_t rom_size;
	uint8_t ram_size;

    // Read in header
    fread(header, 0x180, 1, rom_file);

    // Read in name
    memset(name, '\0', 17);
    for(int i = 0; i < 15; i++) {
        name[i] = header[i + 0x134];
    }
    name[15] = '\0'; // ensure null-terminated even if title used all 15 bytes
    uint8_t cgbFlag = header[143]; // 0x143, (not needed in basic implementation)
    printf("ROM Name: %s\n", name);

    rom_type = header[0x147];
    rom_size = 32 * (1 << header[0x148]);
    ram_size = header[0x149];
    
    if (rom_type == 0x00) { // Exit if the ROM is not a plain 32KB ROM (no mappers)
    printf("ROM Type: ROM ONLY\n");
        
    }
    else {
        printf("This ROM type is not supported\n");
        fclose(rom_file);
        return;
    }

    if (rom_size != 32) {
        printf("ROM must be 32KB\n");
        fclose(rom_file);
        return;
    }
    printf("ROM Size (KB): %d\n", rom_size);

    // READ THE ROM INTO CART
    fread(cart, 1, size, rom_file); 
    
    fclose(rom_file);
}