#pragma once

#define ROM_NAME_OFFSET 0x134
#define ROM_TYPE_OFFSET 0x147
#define ROM_SIZE_OFFSET 0x148
#define ROM_RAM_SIZE_OFFSET 0x149


uint8_t* load_rom(char* filename);
