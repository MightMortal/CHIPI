#ifndef CHIPI_8_OPCODES
#define CHIPI_8_OPCODES
/*
 * CHIPI
 * CHIP-8 Interpreter writed in Plain C
 * Author: MightMortal
 * © 2013 MightMortal
 * Licence: -----
 */

#include "data_types.h"

// 0NNN - Calls RCA 1802 program at address NNN.
void op_0NNN(WORD opcode, CHIP_8_CPU *cpu);
// 00E0 - Clears the screen.
void op_00E0(WORD opcode, CHIP_8_CPU *cpu);
// 00EE - Returns from a subroutine.
int  op_00EE(WORD opcode, CHIP_8_CPU *cpu);
// 1NNN - Jumps to address NNN.
void op_1NNN(WORD opcode, CHIP_8_CPU *cpu);
// 2NNN - Calls subroutine at NNN.
int  op_2NNN(WORD opcode, CHIP_8_CPU *cpu);
// 3XNN - Skips the next instruction if VX equals NN.
void op_3XNN(WORD opcode, CHIP_8_CPU *cpu);
// 4XNN - Skips the next instruction if VX doesn't equal NN.
void op_4XNN(WORD opcode, CHIP_8_CPU *cpu);
// 5XY0 - Skips the next instruction if VX equals VY.
void op_5XY0(WORD opcode, CHIP_8_CPU *cpu);
// 6XNN - Sets VX to NN.
void op_6XNN(WORD opcode, CHIP_8_CPU *cpu);
// 7XNN - Adds NN to VX.
void op_7XNN(WORD opcode, CHIP_8_CPU *cpu);
// 8XY0 - Sets VX to the value of VY.
void op_8XY0(WORD opcode, CHIP_8_CPU *cpu);
// 8XY1 - Sets VX to VX or VY.
void op_8XY1(WORD opcode, CHIP_8_CPU *cpu);
// 8XY2 - Sets VX to VX and VY.
void op_8XY2(WORD opcode, CHIP_8_CPU *cpu);
// 8XY3 - Sets VX to VX xor VY.
void op_8XY3(WORD opcode, CHIP_8_CPU *cpu);
// 8XY4 - Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't.
void op_8XY4(WORD opcode, CHIP_8_CPU *cpu);
// 8XY5 - VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
void op_8XY5(WORD opcode, CHIP_8_CPU *cpu);
// 8XY6 - Shifts VX right by one. VF is set to the value of the least significant bit of VX.
void op_8XY6(WORD opcode, CHIP_8_CPU *cpu);
// 8XY7 - Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
void op_8XY7(WORD opcode, CHIP_8_CPU *cpu);
// 8XYE - Shifts VX left by one. VF is set to the value of the most significant bit of VX.
void op_8XYE(WORD opcode, CHIP_8_CPU *cpu);
// 9XY0 - Skips the next instruction if VX doesn't equal VY.
void op_9XY0(WORD opcode, CHIP_8_CPU *cpu);
// ANNN - Sets I to the address NNN.
void op_ANNN(WORD opcode, CHIP_8_CPU *cpu);
// BNNN - Jumps to the address NNN plus V0.
void op_BNNN(WORD opcode, CHIP_8_CPU *cpu);
// CXNN - Sets VX to a random number and NN.
void op_CXNN(WORD opcode, CHIP_8_CPU *cpu);
// DXYN - Draws a sprite at coordinate (VX, VY) that has a height of N pixels.
void op_DXYN(WORD opcode, CHIP_8_CPU *cpu);
// EX9E - Skips the next instruction if the key stored in VX is pressed.
void op_EX9E(WORD opcode, CHIP_8_CPU *cpu);
// EXA1 - Skips the next instruction if the key stored in VX isn't pressed.
void op_EXA1(WORD opcode, CHIP_8_CPU *cpu);
// FX07 - Sets VX to the value of the delay timer.
void op_FX07(WORD opcode, CHIP_8_CPU *cpu);
// FX0A - A key press is awaited, and then stored in VX.
void op_FX0A(WORD opcode, CHIP_8_CPU *cpu);
// FX15 - Sets the delay timer to VX.
void op_FX15(WORD opcode, CHIP_8_CPU *cpu);
// FX18 - Sets the sound timer to VX.
void op_FX18(WORD opcode, CHIP_8_CPU *cpu);
// FX1E - Adds VX to I.
void op_FX1E(WORD opcode, CHIP_8_CPU *cpu);
// FX29 - Sets I to the location of the sprite for the character in VX.
void op_FX29(WORD opcode, CHIP_8_CPU *cpu);
// FX33 - Stores the Binary-coded decimal representation of VX
void op_FX33(WORD opcode, CHIP_8_CPU *cpu);
// FX55 - Stores V0 to VX in memory starting at address I.
void op_FX55(WORD opcode, CHIP_8_CPU *cpu);
// FX65 - Fills V0 to VX with values from memory starting at address I.
void op_FX65(WORD opcode, CHIP_8_CPU *cpu);

#endif /* CHIPI_8_OPCODES */
