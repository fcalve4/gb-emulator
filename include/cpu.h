#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>




void init();

void set_flag(uint8_t flag);
void clear_flag(uint8_t flag);
int is_flag_set(uint8_t flag);

uint8_t inc8(uint8_t value);
uint8_t dec8(uint8_t value);


int step();
