#include <stdio.h>
#include <SDL2/SDL.h>

#include "rom.h"
#include "memory.h"
#include "cpu.h"

#define WIDTH 900
#define HEIGHT 600

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("gb-emulator",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    

    uint8_t* rom_buffer = load_rom("roms/Tetris.gb");
    
    SDL_Delay(6000);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}