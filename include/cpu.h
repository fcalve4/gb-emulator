#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

struct gb_cpu {
    // Registers A-L
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t f;
    uint8_t g;
    uint8_t h;
    uint8_t l;

};