/*
 * CHIPI
 * CHIP-8 Interpreter writed in Plain C
 * Author: MightMortal
 * © 2013 MightMortal
 * Licence: -----
 */
#include "cpu.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "opcodes.h"
#include "io.h"
#include "memory.h"

void load_font(CHIP_8_CPU* cpu);

CHIP_8_CPU *init_cpu(char* file_name) {
  CHIP_8_CPU *cpu;
  cpu = (CHIP_8_CPU*) malloc(sizeof(*cpu));

  cpu->_ram = init_chip8_memory();
  if (memory_load_rom(cpu->_ram, file_name) != RESULT_SUCCESSFUL) {
    return NULL;
  }

  memset(cpu->_vram, 0, sizeof(cpu->_vram));
  memset(cpu->_stack, 0, sizeof(cpu->_stack));
  memset(cpu->_vRegisters, 0, sizeof(cpu->_vRegisters));

  cpu->_stackCounter = 0;
  cpu->_iRegister = 0;
  cpu->_delayTimer = 0;
  cpu->_soundTimer = 0;
  cpu->_memoryOffset = 0x200; // User code starts from 0x200
  cpu->_keys = 0;

  return cpu;
}

int cpu_tick(CHIP_8_CPU* cpu) {
  WORD opcode = 0x0000;

  // Getting opcode from memory
  opcode = memory_read_word(cpu->_ram, cpu->_memoryOffset);
  cpu->_memoryOffset += 2;
  cpu->_delayTimer--;

  if (cpu->_memoryOffset > 4094)
    cpu->_memoryOffset = 4094;

  switch ((opcode & 0xF000) >> 12) {
    case 0x0:
      switch (opcode) {
      case 0x00E0:
        op_00E0(opcode, cpu);
        break;
      case 0x00EE:
        if (op_00EE(opcode, cpu) != RESULT_SUCCESSFUL)
          return RESULT_ERROR;
        break;
      default:
        op_0NNN(opcode, cpu);
        break;
      }
      break;
    case 0x1:
      op_1NNN(opcode, cpu);
      break;
    case 0x2:
      if (op_2NNN(opcode, cpu) != RESULT_SUCCESSFUL)
        return RESULT_ERROR;
      break;
    case 0x3:
      op_3XNN(opcode, cpu);
      break;
    case 0x4:
      op_4XNN(opcode, cpu);
      break;
    case 0x5:
      op_5XY0(opcode, cpu);
      break;
    case 0x6:
      op_6XNN(opcode, cpu);
      break;
    case 0x7:
      op_7XNN(opcode, cpu);
      break;
    case 0x8:
      switch (opcode & 0x000F) {
      case 0x0:
        op_8XY0(opcode, cpu);
        break;
      case 0x1:
        op_8XY1(opcode, cpu);
        break;
      case 0x2:
        op_8XY2(opcode, cpu);
        break;
      case 0x3:
        op_8XY3(opcode, cpu);
        break;
      case 0x4:
        op_8XY4(opcode, cpu);
        break;
      case 0x5:
        op_8XY5(opcode, cpu);
        break;
      case 0x6:
        op_8XY6(opcode, cpu);
        break;
      case 0x7:
        op_8XY7(opcode, cpu);
        break;
      case 0xE:
        op_8XYE(opcode, cpu);
        break;
      default:
        printf("Unknown opcode\n");
        break;
      }
      break;
    case 0x9:
      op_9XY0(opcode, cpu);
      break;
    case 0xA:
      op_ANNN(opcode, cpu);
      break;
    case 0xB:
      op_BNNN(opcode, cpu);
      break;
    case 0xC:
      op_CXNN(opcode, cpu);
      break;
    case 0xD:
      op_DXYN(opcode, cpu);
      break;
    case 0xE:
      switch (opcode & 0x00FF) {
      case 0x9E:
        op_EX9E(opcode, cpu);
        break;
      case 0xA1:
        op_EXA1(opcode, cpu);
        break;
      default:
        printf("Unknown opcode\n");
        break;
      }
      break;
    case 0xF:
      switch (opcode & 0x00FF) {
      case 0x07:
        op_FX07(opcode, cpu);
        break;
      case 0x0A:
        op_FX0A(opcode, cpu);
        break;
      case 0x15:
        op_FX15(opcode, cpu);
        break;
      case 0x18:
        op_FX18(opcode, cpu);
        break;
      case 0x1E:
        op_FX1E(opcode, cpu);
        break;
      case 0x29:
        op_FX29(opcode, cpu);
        break;
      case 0x33:
        op_FX33(opcode, cpu);
        break;
      case 0x55:
        op_FX55(opcode, cpu);
        break;
      case 0x65:
        op_FX65(opcode, cpu);
        break;
      default:
        printf("Unknown opcode\n");
        break;
      }
      break;
  }
  return RESULT_SUCCESSFUL;
}

void deinit_cpu(CHIP_8_CPU* cpu) {
    deinit_chip8_memory(cpu->_ram);
    cpu->_ram = NULL;
    free(cpu);
}
