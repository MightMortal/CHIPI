#ifndef CHIPI_8_TYPES
#define CHIPI_8_TYPES
/*
 * CHIPI
 * CHIP-8 Interpreter writed in Plain C
 * Author: MightMortal
 * © 2013 MightMortal
 * Licence: -----
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

typedef struct CHIP_8_CPU_ {
	BYTE _ram[MEMORY_SIZE];                  // RAM
	BYTE _vram[SCREEN_WIDTH][SCREEN_HEIGHT]; // Video RAM
	WORD _stack[STACK_SIZE];                 // Stack, 32 bits per level, 16 levels
	BYTE _stackCounter;                      // Stack Counter
	BYTE _vRegisters[16];                    // 16 Registers(V0..VF), 8 bits each
	WORD _iRegister;                         // I register, size 16 bits
	BYTE _delayTimer;                        // Delay timer
	BYTE _soundTimer;                        // Sound timer
	WORD _memoryOffset;                      // Current memory offset
	WORD _keys;                              // Keyboard input
} CHIP_8_CPU;

#endif /* CHIPI_8_TYPES */
