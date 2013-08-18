#ifndef CHIPI_8_MEMORY
#define CHIPI_8_MEMORY
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

typedef BYTE* CHIP_8_MEMORY;

CHIP_8_MEMORY init_chip8_memory();
BYTE memory_read_byte(CHIP_8_MEMORY memory, WORD addr);
WORD memory_read_word(CHIP_8_MEMORY memory, WORD addr);
void memory_write_byte(CHIP_8_MEMORY memory, WORD addr, BYTE value);
void deinit_chip8_memory(CHIP_8_MEMORY memory);
int memory_load_rom(CHIP_8_MEMORY memory, char* file_name);

#endif /* CHIPI_8_MEMORY */
