#include "cpu.h"

struct registers registers;

uint16_t sp;
uint16_t pc;

init_cpu() {
    registers.a = 0;
    registers.b = 0;
    registers.c = 0;
    registers.d = 0;
    registers.e = 0;
    registers.f = 0;
    registers.h = 0;
    registers.l = 0;

}