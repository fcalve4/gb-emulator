# gb-emulator

A Game Boy emulator written in C, using SDL2 for windowing and rendering. This emulator currently only supports 32KB ROMs without mappers (ex. Tetris).

This project is being built from scratch as a learning exercise in emulation and C programming.

> **Status:** early / work in progress


## Getting Started

### Prerequisites

- Windows with a MinGW-w64 `gcc` toolchain (the [`Makefile`](Makefile) is written for `mingw32-make` / GNU Make on Windows)
- [SDL2](https://www.libsdl.org/) development libraries for MinGW


### Build

```sh
make
```

This compiles the sources in `src/` into `obj/` and links `emulator.exe` with SDL2.

### Run

```sh
./emulator.exe
```

`SDL2.dll` needs to be included alongside `emulator.exe`.


## Usage



## Project Structure

```
gb-emulator/
├── include/          # Header files
│   ├── cpu.h
│   ├── memory.h
│   ├── registers.h
│   └── rom.h
├── src/               # Source files
│   ├── cpu.c          
│   ├── memory.c
│   ├── registers.c
│   ├── rom.c
│   └── main.c
├── roms/              # Sample ROMs 
├── Makefile
└── SDL2.dll
```

## Resources

- [Cinoop](https://cturt.github.io/cinoop.html) — emulator that inspired this project
- [Pan Docs](https://gbdev.io/pandocs/) — Game Boy technical reference
- [gbdev.io](https://gbdev.io/) — general Game Boy development resources and tooling
- [SDL2](https://www.libsdl.org/) - window and rendering 
