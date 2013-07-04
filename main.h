#ifndef CHIPI_8_MAIN
#define CHIPI_8_MAIN
#include "data_types.h"
/*
 * CHIPI
 * CHIP-8 Interpreter writed in Plain C
 * Author: MightMortal
 * © 2013 MightMortal
 * Licence: -----
 */

CHIP_8_CPU* init_cpu(char* file_name);
void load_font(CHIP_8_CPU* cpu);
void start_emulation(CHIP_8_CPU* cpu);
void get_input(CHIP_8_CPU* cpu);

#endif /* CHIPI_8_MAIN */
