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

#define REG_X(opcode) (opcode & 0x0F00 >> 8)
#define REG_Y(opcode) (opcode & 0x00F0 >> 4)

void disasm_rom(char* rom_file_path, char* output_file_path) {
    CHIP_8_MEMORY memory = init_chip8_memory();
    memory_load_rom(memory, rom_file_path);
    WORD memory_offset = 0x200;
    WORD opcode = 0x0000;
    FILE* output_file = fopen(output_file_path, "w");
    
    while (memory_offset < 4094) {
        // Getting opcode from memory
        opcode = memory_read_word(memory, memory_offset);
        if (opcode == 0x0000) {
            break;
        }
        fprintf(output_file, "0x%X:\t", memory_offset);
        memory_offset += 2;
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
    
    fflush(output_file);
    fclose(output_file);
    deinit_chip8_memory(memory);
}