/*
 * CHIPI
 * CHIP-8 Interpreter writed in Plain C
 * Author: MightMortal
 * © 2013 MightMortal
 * Licence: -----
 */
#include "disasm.h"
#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "s_list.h"

#define REG_X(opcode) (opcode & 0x0F00 >> 8)
#define REG_Y(opcode) (opcode & 0x00F0 >> 4)

typedef struct CHIP8_DISASM_SECTION_ {
    WORD start;
    WORD end;
} CHIP8_DISASM_SECTION;

void write_opcode_mnemonic(FILE* output_file, WORD opcode);
void get_code_segments_list(CHIP_8_MEMORY memory, S_LIST* list);
void code_segment_bounds_check(CHIP_8_MEMORY memory, WORD start, S_LIST* list);
BYTE word_is_code(CHIP_8_MEMORY memory, WORD addr, S_LIST* list);

void disasm_rom(char* rom_file_path, char* output_file_path) {
  CHIP_8_MEMORY memory = init_chip8_memory();
  memory_load_rom(memory, rom_file_path);
  WORD memory_offset = 0x200;
  WORD opcode = 0x0000;
  FILE* output_file = fopen(output_file_path, "w");
  S_LIST* code_segments_list = s_list_create();
  get_code_segments_list(memory, code_segments_list);

  while (memory_offset < 4094) {
    if (word_is_code(memory, memory_offset, code_segments_list)) {
      // Getting opcode from memory
      opcode = memory_read_word(memory, memory_offset);
      if (opcode == 0x0000) {
        break;
      }
      fprintf(output_file, "0x%X:\t", memory_offset);
      write_opcode_mnemonic(output_file, opcode);
    }
    memory_offset += 2;
  }

  fflush(output_file);
  fclose(output_file);
  s_list_destroy(code_segments_list);
  deinit_chip8_memory(memory);
}

void write_opcode_mnemonic(FILE* output_file, WORD opcode) {
  switch ((opcode & 0xF000) >> 12) {
  case 0x0:
    switch (opcode) {
    case 0x00E0:
      fprintf(output_file, "CLS\n");
      break;
    case 0x00EE:
      fprintf(output_file, "RET\n");
      break;
    default:
      fprintf(output_file, "SYS [0x%X]\n", opcode & 0x0FFF);
      break;
    }
    break;
  case 0x1:
    fprintf(output_file, "JP 0[x%X]\n", opcode & 0x0FFF);
    break;
  case 0x2:
    fprintf(output_file, "CALL [0x%X]\n", opcode & 0x0FFF);
    break;
  case 0x3:
    fprintf(output_file, "SE V%X, %X\n", REG_X(opcode), opcode & 0x00FF);
    break;
  case 0x4:
    fprintf(output_file, "SNE V%X, %X\n", REG_X(opcode), opcode & 0x00FF);
    break;
  case 0x5:
    fprintf(output_file, "SE V%X, V%X\n", REG_X(opcode), REG_Y(opcode));
    break;
  case 0x6:
    fprintf(output_file, "LD V%X, %X\n", REG_X(opcode), opcode & 0x00FF);
    break;
  case 0x7:
    fprintf(output_file, "ADD V%X, %X\n", REG_X(opcode), opcode & 0x00FF);
    break;
  default:
    fprintf(output_file, "Unknown opcode\n");
    break;
  case 0x8:
    switch (opcode & 0x000F) {
    case 0x0:
      fprintf(output_file, "LD V%X, V%X\n", REG_X(opcode), REG_Y(opcode));
      break;
    case 0x1:
      fprintf(output_file, "OR V%X, V%X\n", REG_X(opcode), REG_Y(opcode));
      break;
    case 0x2:
      fprintf(output_file, "AND V%X, V%X\n", REG_X(opcode), REG_Y(opcode));
      break;
    case 0x3:
      fprintf(output_file, "XOR V%X, V%X\n", REG_X(opcode), REG_Y(opcode));
      break;
    case 0x4:
      fprintf(output_file, "ADD V%X, V%X\n", REG_X(opcode), REG_Y(opcode));
      break;
    case 0x5:
      fprintf(output_file, "SUB V%X, V%X\n", REG_X(opcode), REG_Y(opcode));
      break;
    case 0x6:
      fprintf(output_file, "SHR V%X{, V%X}\n", REG_X(opcode), REG_Y(opcode));
      break;
    case 0x7:
      fprintf(output_file, "SUBN V%X, V%X\n", REG_X(opcode), REG_Y(opcode));
      break;
    case 0xE:
      fprintf(output_file, "SHL V%X{, V%X}\n", REG_X(opcode), REG_Y(opcode));
      break;
    default:
      printf("Unknown opcode\n");
      break;
    }
    break;
  case 0x9:
    fprintf(output_file, "SNE V%X, V%X\n", REG_X(opcode), REG_Y(opcode));
    break;
  case 0xA:
    fprintf(output_file, "LD I, [0x%X]\n", opcode & 0x0FFF);
    break;
  case 0xB:
    fprintf(output_file, "JP V0, [0x%X]\n", opcode & 0x0FFF);
    break;
  case 0xC:
    fprintf(output_file, "RND V%X, %X\n", REG_X(opcode), opcode & 0x00FF);
    break;
  case 0xD:
    fprintf(output_file, "DRW V%X, V%X, %X\n", REG_X(opcode), REG_Y(opcode), opcode & 0x000F);
    break;
  case 0xE:
    switch (opcode & 0x00FF) {
    case 0x9E:
      fprintf(output_file, "SKP V%X\n", REG_X(opcode));
      break;
    case 0xA1:
      fprintf(output_file, "SKNP V%X\n", REG_X(opcode));
      break;
    default:
      printf("Unknown opcode\n");
      break;
    }
    break;
  case 0xF:
    switch (opcode & 0x00FF) {
    case 0x07:
      fprintf(output_file, "LD V%X, DT\n", REG_X(opcode));
      break;
    case 0x0A:
      fprintf(output_file, "LD V%X, K\n", REG_X(opcode));
      break;
    case 0x15:
      fprintf(output_file, "LD DT, V%X\n", REG_X(opcode));
      break;
    case 0x18:
      fprintf(output_file, "LD ST, V%X\n", REG_X(opcode));
      break;
    case 0x1E:
      fprintf(output_file, "ADD I, V%X\n", REG_X(opcode));
      break;
    case 0x29:
      fprintf(output_file, "LD F, V%X\n", REG_X(opcode));
      break;
    case 0x33:
      fprintf(output_file, "LD B, V%X\n", REG_X(opcode));
      break;
    case 0x55:
      fprintf(output_file, "LD [I], V%X\n", REG_X(opcode));
      break;
    case 0x65:
      fprintf(output_file, "LD V%X, [I]\n", REG_X(opcode));
      break;
    default:
      printf("Unknown opcode\n");
      break;
    }
  break;
  }
}

void get_code_segments_list(CHIP_8_MEMORY memory, S_LIST* list) {
  code_segment_bounds_check(memory, 0x200, list);
  // TODO: Merging segments
}

void code_segment_bounds_check(CHIP_8_MEMORY memory, WORD start, S_LIST* list) {
  for (int i = 0; i < list->size; i++) {
    CHIP8_DISASM_SECTION* section = (CHIP8_DISASM_SECTION*)s_list_get_element(list, i);
    if (section->start == start) { // This section already checked
      return;
    }
  }
  CHIP8_DISASM_SECTION* code_section = (CHIP8_DISASM_SECTION*)malloc(sizeof(CHIP8_DISASM_SECTION));
  s_list_push(list, code_section);
  code_section->start = start;
  WORD pc = start;
  WORD opcode = 0x0000;
  while (1) {
    opcode = memory_read_word(memory, pc);
    if ((opcode & 0xF000) == 0x2000 || (opcode & 0xF000) == 0x1000 || (opcode & 0xF000) == 0xB000) {
      code_segment_bounds_check(memory, opcode & 0x0FFF, list);
    }
    if ((opcode & 0xF000) == 0x1000 || opcode == 0x00EE || (opcode & 0xF000) == 0xB000) {
      WORD prev_opcode  = memory_read_word(memory, pc - 2);
      WORD m_nibble = (prev_opcode & 0xF000) >> 12;
      if (m_nibble != 3 && m_nibble != 4 && m_nibble != 5 // Prev instruction is jump, this is not end of section
          && (prev_opcode & 0xF0FF) != 0xE09E
          && (prev_opcode & 0xF0FF) != 0xE0A1) {
          code_section->end = pc;
          break;
        }
    }
    pc += 2;
  }
}

BYTE word_is_code(CHIP_8_MEMORY memory, WORD addr, S_LIST* list) {
  for (int i = 0; i < list->size; i++) {
    CHIP8_DISASM_SECTION* segment = (CHIP8_DISASM_SECTION*)s_list_get_element(list, i);
      if (addr >= segment->start && addr <= segment->end) {
        return 1;
      }
  }
  return 0;
}
