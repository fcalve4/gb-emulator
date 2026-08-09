# gb-emulator
A Gameboy emulator written in C





# Compiling
```export DISPLAY=host.docker.internal:0.0```

```gcc main.c -o main.o $(sdl2-config --cflags --libs)```