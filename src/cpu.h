#ifndef CHIPI_8_CPU
#define CHIPI_8_CPU
/*
 * CHIPI
 * CHIP-8 Interpreter writed in Plain C
 * Author: MightMortal
 * Licence: Apache Licence
 * Copyright 2013 MightMortal
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
