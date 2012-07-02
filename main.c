#include "include/main.h"
#include "include/opcodes.h"
#include "include/render.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <GL/glfw.h>
/*
 * Main implementation for CHIP-8 emulator
 * Implementation
 * Author: MightMortal
 */

int running = 0;

CHIP_8_CPU *init_cpu(char* file_name) {
	CHIP_8_CPU *cpu;
	cpu = (CHIP_8_CPU*) malloc(sizeof(*cpu));
	memset(cpu->_ram, 0, sizeof(cpu->_ram));
	memset(cpu->_vram, 0, sizeof(cpu->_vram));
	memset(cpu->_stack, 0, sizeof(cpu->_stack));
	memset(cpu->_vRegisters, 0, sizeof(cpu->_vRegisters));
	cpu->_stackCounter = 0;
	cpu->_iRegister = 0;
	cpu->_delayTimer = 0;
	cpu->_soundTimer = 0;
	cpu->_memoryOffset = 0x200; // User code starts from 0x200
	cpu->_keys = 0;
	load_font(cpu);
	FILE * pFile;
	pFile = fopen(file_name, "rb");
	if (pFile == NULL )
		return NULL ;

	fread(&(cpu->_ram[0x200]), 4096 - 0x200, 1, pFile);
	fclose(pFile);

	return cpu;
}

void load_font(CHIP_8_CPU* cpu) {
	// "0"
	cpu->_ram[0] = 0xF0;
	cpu->_ram[1] = 0x90;
	cpu->_ram[2] = 0x90;
	cpu->_ram[3] = 0x90;
	cpu->_ram[4] = 0xF0;
	// "1"
	cpu->_ram[5] = 0x20;
	cpu->_ram[6] = 0x60;
	cpu->_ram[7] = 0x20;
	cpu->_ram[8] = 0x20;
	cpu->_ram[9] = 0x70;
	// "2"
	cpu->_ram[10] = 0xF0;
	cpu->_ram[11] = 0x10;
	cpu->_ram[12] = 0xF0;
	cpu->_ram[13] = 0x80;
	cpu->_ram[14] = 0xF0;
	// "3"
	cpu->_ram[15] = 0xF0;
	cpu->_ram[16] = 0x10;
	cpu->_ram[17] = 0xF0;
	cpu->_ram[18] = 0x10;
	cpu->_ram[19] = 0xF0;
	// "4"
	cpu->_ram[20] = 0x90;
	cpu->_ram[21] = 0x90;
	cpu->_ram[22] = 0xF0;
	cpu->_ram[23] = 0x10;
	cpu->_ram[24] = 0x10;
	// "5"
	cpu->_ram[25] = 0xF0;
	cpu->_ram[26] = 0x80;
	cpu->_ram[27] = 0xF0;
	cpu->_ram[28] = 0x10;
	cpu->_ram[29] = 0xF0;
	// "6"
	cpu->_ram[30] = 0xF0;
	cpu->_ram[31] = 0x80;
	cpu->_ram[32] = 0xF0;
	cpu->_ram[33] = 0x90;
	cpu->_ram[34] = 0xF0;
	// "7"
	cpu->_ram[35] = 0xF0;
	cpu->_ram[36] = 0x10;
	cpu->_ram[37] = 0x20;
	cpu->_ram[38] = 0x40;
	cpu->_ram[39] = 0x40;
	// "8"
	cpu->_ram[40] = 0xF0;
	cpu->_ram[41] = 0x90;
	cpu->_ram[42] = 0xF0;
	cpu->_ram[43] = 0x90;
	cpu->_ram[44] = 0xF0;
	// "9"
	cpu->_ram[45] = 0xF0;
	cpu->_ram[46] = 0x90;
	cpu->_ram[47] = 0xF0;
	cpu->_ram[48] = 0X10;
	cpu->_ram[49] = 0XF0;
	// "A"
	cpu->_ram[50] = 0xF0;
	cpu->_ram[51] = 0x90;
	cpu->_ram[52] = 0xF0;
	cpu->_ram[53] = 0x90;
	cpu->_ram[54] = 0x90;
	// "B"
	cpu->_ram[55] = 0xE0;
	cpu->_ram[56] = 0x90;
	cpu->_ram[57] = 0xE0;
	cpu->_ram[58] = 0x90;
	cpu->_ram[59] = 0xE0;
	// "C"
	cpu->_ram[60] = 0xF0;
	cpu->_ram[61] = 0x80;
	cpu->_ram[62] = 0x80;
	cpu->_ram[63] = 0x80;
	cpu->_ram[64] = 0xF0;
	// "D"
	cpu->_ram[65] = 0xE0;
	cpu->_ram[66] = 0x90;
	cpu->_ram[67] = 0x90;
	cpu->_ram[68] = 0x90;
	cpu->_ram[69] = 0xE0;
	// "E"
	cpu->_ram[70] = 0xF0;
	cpu->_ram[71] = 0x80;
	cpu->_ram[72] = 0xF0;
	cpu->_ram[73] = 0x80;
	cpu->_ram[74] = 0xF0;
	// "F"
	cpu->_ram[75] = 0xF0;
	cpu->_ram[76] = 0x80;
	cpu->_ram[77] = 0xF0;
	cpu->_ram[78] = 0x80;
	cpu->_ram[79] = 0x80;
}

void get_input(CHIP_8_CPU* cpu) {
	cpu->_keys = 255;
	if (glfwGetKey('1'))
		cpu->_keys = 0x1;
	else if (glfwGetKey('2'))
		cpu->_keys = 0x2;
	else if (glfwGetKey('3'))
		cpu->_keys = 0x3;
	else if (glfwGetKey('Q'))
		cpu->_keys = 0x4;
	else if (glfwGetKey('W'))
		cpu->_keys = 0x5;
	else if (glfwGetKey('E'))
		cpu->_keys = 0x6;
	else if (glfwGetKey('A'))
		cpu->_keys = 0x7;
	else if (glfwGetKey('S'))
		cpu->_keys = 0x8;
	else if (glfwGetKey('D'))
		cpu->_keys = 0x9;
	else if (glfwGetKey('X'))
		cpu->_keys = 0x0;
	else if (glfwGetKey('Z'))
		cpu->_keys = 0xA;
	else if (glfwGetKey('C'))
		cpu->_keys = 0xB;
	else if (glfwGetKey('4'))
		cpu->_keys = 0xC;
	else if (glfwGetKey('R'))
		cpu->_keys = 0xD;
	else if (glfwGetKey('F'))
		cpu->_keys = 0xE;
	else if (glfwGetKey('V'))
		cpu->_keys = 0xF;
}

void start_emulation(CHIP_8_CPU* cpu) {
	clock_t last_time = clock();
	clock_t new_time = clock();
	clock_t unprocessed = 0;
	const clock_t clock_per_tick = CLOCKS_PER_SEC / 400;
	running = 1;
	while (running) {
		// Main loop
		last_time = new_time;
		new_time = clock();
		unprocessed += new_time - last_time;
		while (unprocessed > clock_per_tick) {
			get_input(cpu);
			WORD opcode;

			// Getting opcode from memory
			opcode = (cpu->_ram[cpu->_memoryOffset] << 8)
					+ cpu->_ram[cpu->_memoryOffset + 1];
			cpu->_memoryOffset += 2;
			cpu->_delayTimer--;

			if (cpu->_memoryOffset > 4096)
				cpu->_memoryOffset = 4096;
			switch ((opcode & 0xF000) >> 12) {
			case 0x0:
				switch (opcode) {
				case 0x00E0:
					op_00E0(opcode, cpu);
					break;
				case 0x00EE:
					if (op_00EE(opcode, cpu) != RESULT_SUCCESSFUL)
						return;
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
					return;
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
			unprocessed -= clock_per_tick;
		}
		render(cpu);
		glfwSleep(1 / 60);
		running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
	}
}

int main(int argc, char** argv) {
	CHIP_8_CPU *cpu = NULL;

	if (argc < 2) {
		printf("You must send rom file in the arguments\n");
		printf("Example: chipi8.exe my_game.rom\n");
		return 1;
	}
	if (init_render() == RESULT_ERROR) {
		printf("can't init render");
		return 1;
	}

	cpu = init_cpu(argv[1]);

	if (cpu != 0) {
		start_emulation(cpu);
		exit_render();
	} else {
		printf("Can't init CPU or load rom\n");
		return 1;
	}

	return 0;
}
