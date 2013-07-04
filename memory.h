#ifndef CHIPI_8_MEMORY
#define CHIPI_8_MEMORY
/*
 * CHIPI
 * CHIP-8 Interpreter writed in Plain C
 * Author: MightMortal
 * © 2013 MightMortal
 * Licence: -----
 */
#include "data_types.h"

typedef BYTE* CHIP_8_MEMORY;

CHIP_8_MEMORY init_chip8_memory();
BYTE memory_read_byte(CHIP_8_MEMORY memory, WORD addr);
WORD memory_read_word(CHIP_8_MEMORY memory, WORD addr);
void memory_write_byte(CHIP_8_MEMORY memory, WORD addr, BYTE value);
void deinit_chip8_memory(CHIP_8_MEMORY memory);
int memory_load_rom(CHIP_8_MEMORY memory, char* file_name);

#endif /* CHIPI_8_MEMORY */
