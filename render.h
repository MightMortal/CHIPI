#ifndef RENDER_H_
#define RENDER_H_
#include "data_types.h"
/*
 * CHIPI
 * CHIP-8 Interpreter writed in Plain C
 * Author: MightMortal
 * © 2013 MightMortal
 * Licence: -----
 */

int init_render();
void deinit_render();
void render(CHIP_8_CPU* cpu);

#endif /* RENDER_H_ */
