#ifndef CHIPI_8_TYPES
#define CHIPI_8_TYPES
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

typedef unsigned char BYTE;
typedef unsigned short WORD;

#define RESULT_SUCCESSFUL 0
#define RESULT_ERROR      1

#define SCREEN_WIDTH  64
#define SCREEN_HEIGHT 32

#define MEMORY_SIZE 4096
#define STACK_SIZE 16

#define SPRITE_WIDTH 8

#endif /* CHIPI_8_TYPES */
