/*
 * CHIPI
 * CHIP-8 Interpreter writed in Plain C
 * Author: MightMortal
 * © 2013 MightMortal
 * Licence: -----
 */
#include "memory.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

CHIP_8_MEMORY init_chip8_memory() {
    CHIP_8_MEMORY memory = (CHIP_8_MEMORY)malloc(MEMORY_SIZE);
    memset(memory, 0, MEMORY_SIZE);
    
    memory[0x00] = 0xF0; // ****
	memory[0x01] = 0x90; // *  *
	memory[0x02] = 0x90; // *  *
	memory[0x03] = 0x90; // *  *
	memory[0x04] = 0xF0; // ****
    
	memory[0x05] = 0x20; //   *
	memory[0x06] = 0x60; //  **
	memory[0x07] = 0x20; //   *
	memory[0x08] = 0x20; //   *
	memory[0x09] = 0x70; //  ***
    
	memory[0x0A] = 0xF0; // ****
	memory[0x0B] = 0x10; //    *
	memory[0x0C] = 0xF0; // ****
	memory[0x0D] = 0x80; // *
	memory[0x0E] = 0xF0; // ****
    
	memory[0x0F] = 0xF0; // ****
	memory[0x10] = 0x10; //    *
	memory[0x11] = 0xF0; // ****
	memory[0x12] = 0x10; //    *
	memory[0x13] = 0xF0; // ****
    
	memory[0x14] = 0x90; // *  *
	memory[0x15] = 0x90; // *  *
	memory[0x16] = 0xF0; // ****
	memory[0x17] = 0x10; //    *
	memory[0x18] = 0x10; //    *
    
	memory[0x19] = 0xF0; // ****
	memory[0x1A] = 0x80; // *
	memory[0x1B] = 0xF0; // ****
	memory[0x1C] = 0x10; //    *
	memory[0x1D] = 0xF0; // ****
    
	memory[0x1E] = 0xF0; // ****
	memory[0x1F] = 0x80; // *
	memory[0x20] = 0xF0; // ****
	memory[0x21] = 0x90; // *  *
	memory[0x22] = 0xF0; // ****
    
	memory[0x23] = 0xF0; // ****
	memory[0x24] = 0x10; //    *
	memory[0x25] = 0x20; //   *
	memory[0x26] = 0x40; //  *
	memory[0x27] = 0x40; //  *
    
	memory[0x28] = 0xF0; // ****
	memory[0x29] = 0x90; // *  *
	memory[0x2A] = 0xF0; // ****
	memory[0x2B] = 0x90; // *  *
	memory[0x2C] = 0xF0; // ****
    
	memory[0x2D] = 0xF0; // ****
	memory[0x2E] = 0x90; // *  *
	memory[0x2F] = 0xF0; // ****
	memory[0x30] = 0X10; //    *
	memory[0x31] = 0XF0; // ****
    
	memory[0x32] = 0xF0; // ****
	memory[0x33] = 0x90; // *  *
	memory[0x34] = 0xF0; // ****
	memory[0x35] = 0x90; // *  *
	memory[0x36] = 0x90; // *  *
    
	memory[0x37] = 0xE0; // ***
	memory[0x38] = 0x90; // *  *
	memory[0x39] = 0xE0; // ***
	memory[0x3A] = 0x90; // *  *
	memory[0x3B] = 0xE0; // ***
    
	memory[0x3C] = 0xF0; // ****
	memory[0x3D] = 0x80; // *
	memory[0x3E] = 0x80; // *
	memory[0x3F] = 0x80; // *
	memory[0x40] = 0xF0; // ****
    
	memory[0x41] = 0xE0; // ***
	memory[0x42] = 0x90; // *  *
	memory[0x43] = 0x90; // *  *
	memory[0x44] = 0x90; // *  *
	memory[0x45] = 0xE0; // ***
    
	memory[0x46] = 0xF0; // ****
	memory[0x47] = 0x80; // *
	memory[0x48] = 0xF0; // ****
	memory[0x49] = 0x80; // *
	memory[0x4A] = 0xF0; // ****
    
	memory[0x4B] = 0xF0; // ****
	memory[0x4C] = 0x80; // *
	memory[0x4D] = 0xF0; // ****
	memory[0x4E] = 0x80; // *
	memory[0x4F] = 0x80; // *
    
    return memory;
}

BYTE memory_read_byte(CHIP_8_MEMORY memory, WORD addr) {
    if (addr > MEMORY_SIZE || addr < 0) {
        return -1;
    }
    return memory[addr];
}

WORD memory_read_word(CHIP_8_MEMORY memory, WORD addr) {
    if (addr + 1 > MEMORY_SIZE || addr < 0) {
        return -1;
    }
    return memory[addr] << 8 | memory[addr + 1];
}

void memory_write_byte(CHIP_8_MEMORY memory, WORD addr, BYTE value) {
    if (addr > MEMORY_SIZE || addr < 0) {
        return;
    }
    memory[addr] = value;
}

void deinit_chip8_memory(CHIP_8_MEMORY memory) {
    free(memory);
}

int memory_load_rom(CHIP_8_MEMORY memory, char* file_name) {
	FILE * pFile;
	pFile = fopen(file_name, "rb");
	if (pFile == NULL)
		return RESULT_ERROR;
    
	fread(&memory[0x200], MEMORY_SIZE - 0x200, 1, pFile);
	fclose(pFile);
    
    return RESULT_SUCCESSFUL;
}