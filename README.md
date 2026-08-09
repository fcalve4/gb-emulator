# gb-emulator
A Gameboy emulator written in C

This project was inspired by Cinoop (https://cturt.github.io/cinoop.html)





# Compiling from docker linux container
```export DISPLAY=host.docker.internal:0.0```

```gcc main.c -o main.o $(sdl2-config --cflags --libs)```