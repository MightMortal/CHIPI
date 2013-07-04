/*
 * CHIPI
 * CHIP-8 Interpreter writed in Plain C
 * Author: MightMortal
 * © 2013 MightMortal
 * Licence: -----
 */

#ifndef CHIPI_8_IO
#define CHIPI_8_IO
#include "data_types.h"
#include "cpu.h"

int init_io();
void deinit_io();

void render(CHIP_8_CPU* cpu);

void update_input(WORD* keys);
// void update_sound(word sound_time);

#endif /* CHIPI_8_IO */