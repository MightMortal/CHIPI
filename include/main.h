#ifndef CHIPI_8_MAIN
#define CHIPI_8_MAIN
#include "data_types.h"
/*
 * Main header for CHIP-8 emulator
 * Header
 * Author: MightMortal
 */

CHIP_8_CPU* init_cpu(char* file_name);
void load_font(CHIP_8_CPU* cpu);
void start_emulation(CHIP_8_CPU* cpu);
void get_input(CHIP_8_CPU* cpu);
#endif /* CHIPI_8_MAIN */
