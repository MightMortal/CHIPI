#ifndef RENDER_H_
#define RENDER_H_
#include "data_types.h"
/*
 * Render for CHIP-8 emulator
 * Header
 * Author: MightMortal
 */
int init_render();
void exit_render();
void render(CHIP_8_CPU* cpu);

#endif /* RENDER_H_ */
