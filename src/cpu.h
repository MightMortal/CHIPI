#ifndef CHIPI_8_CPU
#define CHIPI_8_CPU
/*
 * CHIPI
 * CHIP-8 Interpreter writed in Plain C
 * Author: MightMortal
 * © 2013 MightMortal
 * Licence: -----
 */
#include "data_types.h"
#include "memory.h"

typedef struct CHIP_8_CPU_ {
  // BYTE _ram[MEMORY_SIZE];                // RAM
  CHIP_8_MEMORY _ram;
  BYTE _vram[SCREEN_WIDTH][SCREEN_HEIGHT];  // Video RAM
  WORD _stack[STACK_SIZE];                  // Stack, 32 bits per level, 16 levels
  BYTE _stackCounter;                       // Stack Counter
  BYTE _vRegisters[16];                     // 16 Registers(V0..VF), 8 bits each
  WORD _iRegister;                          // I register, size 16 bits
  BYTE _delayTimer;                         // Delay timer
  BYTE _soundTimer;                         // Sound timer
  WORD _memoryOffset;                       // Current memory offset
  WORD _keys;                               // Keyboard input
} CHIP_8_CPU;

CHIP_8_CPU* init_cpu(char* file_name);
int cpu_tick(CHIP_8_CPU* cpu);
void deinit_cpu(CHIP_8_CPU* cpu);

#endif /* CHIPI_8_CPU */
