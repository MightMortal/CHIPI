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

#include "opcodes.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memory.h"

// 0NNN - Calls RCA 1802 program at address NNN.
void op_0NNN(WORD opcode, CHIP_8_CPU *cpu) {
  if (opcode)
    printf("RCA 1802 not implemented.\n");
}

// 00E0 - Clears the screen.
void op_00E0(WORD opcode, CHIP_8_CPU *cpu) {
  memset(cpu->_vram, 0, sizeof(cpu->_vram));
}

// 00EE - Returns from a subroutine.
int op_00EE(WORD opcode, CHIP_8_CPU *cpu) {
  if (cpu->_stackCounter < 1) {
    printf("No address in stack\n");
    return RESULT_ERROR;
  }
  cpu->_stackCounter--;
  cpu->_memoryOffset = cpu->_stack[cpu->_stackCounter];
  cpu->_stack[cpu->_stackCounter] = 0;
  return RESULT_SUCCESSFUL;
}

// 1NNN - Jumps to address NNN.
void op_1NNN(WORD opcode, CHIP_8_CPU *cpu) {
  cpu->_memoryOffset = opcode & 0x0FFF;
}

// 2NNN - Calls subroutine at NNN.
int op_2NNN(WORD opcode, CHIP_8_CPU *cpu) {
  if (cpu->_stackCounter >= 15) {
    printf("Stack overflow\n");
    return RESULT_ERROR;
  }

  cpu->_stack[cpu->_stackCounter] = cpu->_memoryOffset;
  cpu->_memoryOffset = opcode & 0x0FFF;
  cpu->_stackCounter++;
  return RESULT_SUCCESSFUL;
}

// 3XNN - Skips the next instruction if VX equals NN.
void op_3XNN(WORD opcode, CHIP_8_CPU *cpu) {
  BYTE VX = (opcode & 0x0F00) >> 8;

  if (cpu->_vRegisters[VX] == (opcode & 0x00FF))
    cpu->_memoryOffset += 2;
}

// 4XNN - Skips the next instruction if VX doesn't equal NN.
void op_4XNN(WORD opcode, CHIP_8_CPU *cpu) {
  BYTE VX = (opcode & 0x0F00) >> 8;

  if (cpu->_vRegisters[VX] != (opcode & 0x00FF))
    cpu->_memoryOffset += 2;
}

// 5XY0 - Skips the next instruction if VX equals VY.
void op_5XY0(WORD opcode, CHIP_8_CPU *cpu) {
  BYTE VX = (opcode & 0x0F00) >> 8;
  BYTE VY = (opcode & 0x00F0) >> 4;

  if (cpu->_vRegisters[VX] == cpu->_vRegisters[VY])
    cpu->_memoryOffset += 2;
}

// 6XNN - Sets VX to NN.
void op_6XNN(WORD opcode, CHIP_8_CPU *cpu) {
  BYTE VX = (opcode & 0x0F00) >> 8;

  cpu->_vRegisters[VX] = opcode & 0x00FF;
}

// 7XNN - Adds NN to VX.
void op_7XNN(WORD opcode, CHIP_8_CPU *cpu) {
  BYTE VX = (opcode & 0x0F00) >> 8;

  cpu->_vRegisters[VX] += opcode & 0x00FF;
}

// 8XY0 - Sets VX to the value of VY.
void op_8XY0(WORD opcode, CHIP_8_CPU *cpu) {
  BYTE VX = (opcode & 0x0F00) >> 8;
  BYTE VY = (opcode & 0x00F0) >> 4;

  cpu->_vRegisters[VX] = cpu->_vRegisters[VY];
}

// 8XY1 - Sets VX to VX or VY.
void op_8XY1(WORD opcode, CHIP_8_CPU *cpu) {
  BYTE VX = (opcode & 0x0F00) >> 8;
  BYTE VY = (opcode & 0x00F0) >> 4;

  cpu->_vRegisters[VX] = cpu->_vRegisters[VX] | cpu->_vRegisters[VY];
}

// 8XY2 - Sets VX to VX and VY.
void op_8XY2(WORD opcode, CHIP_8_CPU *cpu) {
  BYTE VX = (opcode & 0x0F00) >> 8;
  BYTE VY = (opcode & 0x00F0) >> 4;

  cpu->_vRegisters[VX] = cpu->_vRegisters[VX] & cpu->_vRegisters[VY];
}

// 8XY3 - Sets VX to VX xor VY.
void op_8XY3(WORD opcode, CHIP_8_CPU *cpu) {
  BYTE VX = (opcode & 0x0F00) >> 8;
  BYTE VY = (opcode & 0x00F0) >> 4;

  cpu->_vRegisters[VX] = cpu->_vRegisters[VX] ^ cpu->_vRegisters[VY];
}

// 8XY4 - Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't.
void op_8XY4(WORD opcode, CHIP_8_CPU *cpu) {
  BYTE VX = (opcode & 0x0F00) >> 8;
  BYTE VY = (opcode & 0x00F0) >> 4;

  if (cpu->_vRegisters[VX] + cpu->_vRegisters[VY] > 0xFF)
    cpu->_vRegisters[0xF] = 1;
  else
    cpu->_vRegisters[0xF] = 0;

  cpu->_vRegisters[VX] += cpu->_vRegisters[VY];
}

// 8XY5 - VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
void op_8XY5(WORD opcode, CHIP_8_CPU *cpu) {
  BYTE VX = (opcode & 0x0F00) >> 8;
  BYTE VY = (opcode & 0x00F0) >> 4;

  if (cpu->_vRegisters[VY] > cpu->_vRegisters[VX])
    cpu->_vRegisters[0xF] = 0;
  else
    cpu->_vRegisters[0xF] = 1;

  cpu->_vRegisters[VX] -= cpu->_vRegisters[VY];
}

// 8XY6 - Shifts VX right by one. VF is set to the value of the least significant bit of VX before the shift.
void op_8XY6(WORD opcode, CHIP_8_CPU *cpu) {
  BYTE VX = (opcode & 0x0F00) >> 8;

  cpu->_vRegisters[0xF] = cpu->_vRegisters[VX] & 0x0001;
  cpu->_vRegisters[VX] = cpu->_vRegisters[VX] >> 1;
}

// 8XY7 - Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
void op_8XY7(WORD opcode, CHIP_8_CPU *cpu) {
  BYTE VX = (opcode & 0x0F00) >> 8;
  BYTE VY = (opcode & 0x00F0) >> 4;

  if (cpu->_vRegisters[VX] > cpu->_vRegisters[VY])
    cpu->_vRegisters[0xF] = 1;
  else
    cpu->_vRegisters[0xF] = 0;

  cpu->_vRegisters[VX] = cpu->_vRegisters[VY] - cpu->_vRegisters[VX];
}

// 8XYE - Shifts VX left by one. VF is set to the value of the most significant bit of VX before the shift.
void op_8XYE(WORD opcode, CHIP_8_CPU *cpu) {
  BYTE VX = (opcode & 0x0F00) >> 8;

  cpu->_vRegisters[0xF] = (cpu->_vRegisters[VX] >> 7) & 1;
  cpu->_vRegisters[VX] = cpu->_vRegisters[VX] << 1;
}

// 9XY0 - Skips the next instruction if VX doesn't equal VY.
void op_9XY0(WORD opcode, CHIP_8_CPU *cpu) {
  BYTE VX = (opcode & 0x0F00) >> 8;
  BYTE VY = (opcode & 0x00F0) >> 4;

  if (cpu->_vRegisters[VX] != cpu->_vRegisters[VY])
    cpu->_memoryOffset += 2;
}

// ANNN - Sets I to the address NNN.
void op_ANNN(WORD opcode, CHIP_8_CPU *cpu) {
  cpu->_iRegister = opcode & 0x0FFF;
}

// BNNN - Jumps to the address NNN plus V0.
void op_BNNN(WORD opcode, CHIP_8_CPU *cpu) {
  cpu->_memoryOffset = cpu->_vRegisters[0x0] + (opcode & 0x0FFF);
}

// CXNN - Sets VX to a random number and NN.
void op_CXNN(WORD opcode, CHIP_8_CPU *cpu) {
  BYTE VX = (opcode & 0x0F00) >> 8;
  // CHECK
  cpu->_vRegisters[VX] = (rand() % 0xFF) & (opcode & 0x00FF);
}

/*
 * DXYN - Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels.
 * Each row of 8 pixels is read as bit-coded (with the most significant bit of each byte displayed on the left)
 * starting from memory location I; I value doesn't change after the execution of this instruction.
 * As described above, VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn,
 * and to 0 if that doesn't happen.
 */
void op_DXYN(WORD opcode, CHIP_8_CPU *cpu) {
  BYTE xp = cpu->_vRegisters[(opcode & 0x0F00) >> 8];
  BYTE yp = cpu->_vRegisters[(opcode & 0x00F0) >> 4];
  BYTE h = opcode & 0x000F;
  cpu->_vRegisters[0xF] = 0x0;

  for (int y = cpu->_iRegister; y < cpu->_iRegister + h; y++) {
    BYTE row = memory_read_byte(cpu->_ram, y);

    for (int x = 0; x < SPRITE_WIDTH; x++) {
      BYTE new_pixel = (row >> (7 - x)) & 1;
      int _x = xp + x;
      int _y = yp + y - cpu->_iRegister;
      if (_x >= SCREEN_WIDTH || _y >= SCREEN_HEIGHT)
        continue;
      if (new_pixel) {
        if (cpu->_vram[_x][_y] == 1)
          cpu->_vRegisters[0xF] = 0x1;
        cpu->_vram[_x][_y] = !cpu->_vram[_x][_y];
      }

    }
  }
}

// EX9E - Skips the next instruction if the key stored in VX is pressed.
void op_EX9E(WORD opcode, CHIP_8_CPU *cpu) {
  BYTE VX = (opcode & 0x0F00) >> 8;

  if (cpu->_keys == cpu->_vRegisters[VX])
    cpu->_memoryOffset += 2;
}

// EXA1 - Skips the next instruction if the key stored in VX isn't pressed.
void op_EXA1(WORD opcode, CHIP_8_CPU *cpu) {
  BYTE VX = (opcode & 0x0F00) >> 8;

  if (cpu->_keys != cpu->_vRegisters[VX])
    cpu->_memoryOffset += 2;
}

// FX07 - Sets VX to the value of the delay timer.
void op_FX07(WORD opcode, CHIP_8_CPU *cpu) {
  BYTE VX = (opcode & 0x0F00) >> 8;
  cpu->_vRegisters[VX] = cpu->_delayTimer;
}

// FX0A - A key press is awaited, and then stored in VX.
void op_FX0A(WORD opcode, CHIP_8_CPU *cpu) {
  if (cpu->_keys != 255)
    cpu->_vRegisters[(opcode & 0x0F00) >> 8] = cpu->_keys;
  else
    cpu->_memoryOffset -= 2;
}

// FX15 - Sets the delay timer to VX.
void op_FX15(WORD opcode, CHIP_8_CPU *cpu) {
  BYTE VX = (opcode & 0x0F00) >> 8;
  cpu->_delayTimer = cpu->_vRegisters[VX];
}

// FX18 - Sets the sound timer to VX.
void op_FX18(WORD opcode, CHIP_8_CPU *cpu) {
  BYTE VX = (opcode & 0x0F00) >> 8;
  cpu->_soundTimer = cpu->_vRegisters[VX];
}

// FX1E - Adds VX to I.
void op_FX1E(WORD opcode, CHIP_8_CPU *cpu) {
  BYTE VX = (opcode & 0x0F00) >> 8;

  cpu->_iRegister += cpu->_vRegisters[VX];
}

// FX29 - Sets I to the location of the sprite for the character in VX.
// Characters 0-F (in hexadecimal) are represented by a 4x5 font.
void op_FX29(WORD opcode, CHIP_8_CPU *cpu) {
  BYTE VX = (opcode & 0x0F00) >> 8;
  cpu->_iRegister = cpu->_vRegisters[VX] * 5;
}

// FX33 - Stores the Binary-coded decimal representation of VX,
// with the most significant of three digits at the address in I,
// the middle digit at I plus 1, and the least significant digit at I plus 2.
void op_FX33(WORD opcode, CHIP_8_CPU *cpu) {
  BYTE VX = (opcode & 0x0F00) >> 8;
  BYTE number = cpu->_vRegisters[VX];

  memory_write_byte(cpu->_ram, cpu->_iRegister, number / 100);
  memory_write_byte(cpu->_ram, cpu->_iRegister + 1, (number / 10) % 10);
  memory_write_byte(cpu->_ram, cpu->_iRegister + 2, number % 10);
}

// FX55 - Stores V0 to VX in memory starting at address I.
void op_FX55(WORD opcode, CHIP_8_CPU *cpu) {
  BYTE VX = (opcode & 0x0F00) >> 8;
  WORD _i = cpu->_iRegister;

  for (BYTE i = 0; i <= VX; i++) {
    memory_write_byte(cpu->_ram, _i + i, cpu->_vRegisters[i]);
  }
}

// FX65 - Fills V0 to VX with values from memory starting at address I.
void op_FX65(WORD opcode, CHIP_8_CPU *cpu) {
  BYTE VX = (opcode & 0x0F00) >> 8;
  WORD _i = cpu->_iRegister;

  for (BYTE i = 0; i <= VX; i++) {
    cpu->_vRegisters[i] = memory_read_byte(cpu->_ram, _i + i);
  }
}
