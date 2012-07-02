#ifndef CHIPI_8_TYPES
#define CHIPI_8_TYPES
/*
 * Data types for CHIP-8 emulator
 * Header
 * Author: MightMortal
 */

typedef unsigned char BYTE;
typedef unsigned short WORD;

#define RESULT_SUCCESSFUL 0
#define RESULT_ERROR      1

#define SCREEN_WIDTH  64
#define SCREEN_HEIGHT 32

#define MEMORY_SIZE 4096
#define STACK_SIZE 16

#define SPRITE_WIDTH 8

typedef struct {
	BYTE _ram[MEMORY_SIZE]; // RAM
	BYTE _vram[SCREEN_WIDTH][SCREEN_HEIGHT]; // Video RAM
	WORD _stack[STACK_SIZE]; // Stack, 32 bits per level, 16 levels
	BYTE _stackCounter; // Stack Counter
	BYTE _vRegisters[16]; // 16 Registers(V0..VF), per 8 bits
	WORD _iRegister; // I register, size 16 bits
	BYTE _delayTimer; // Delay timer: This timer is intended to be used for timing the events of games. Its value can be set and read.
	BYTE _soundTimer; // Sound timer: This timer is used for sound effects. When its value is nonzero, a beeping sound is made.
	WORD _memoryOffset; // Current memory offset
	WORD _keys; // Input keyboard
} CHIP_8_CPU;

#endif /* CHIPI_8_TYPES */
