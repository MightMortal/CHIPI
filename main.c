/*
 * CHIPI
 * CHIP-8 Interpreter writed in Plain C
 * Author: MightMortal
 * © 2013 MightMortal
 * Licence: -----
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "include/GL/glfw.h"
#include "data_types.h"
#include "io.h"
#include "disasm.h"

void start_emulation(CHIP_8_CPU* cpu) {
    const unsigned int RUNNING_RATE = 60; // Running rate in Hz. Default is 60Hz
	const double time_per_tick = 1000000 / RUNNING_RATE;
	double last_time = glfwGetTime() * 1000000; // Getting time in ns
	double new_time = glfwGetTime() * 1000000; // Getting time in ns
	double unprocessed = 0;
    
    int running = 1;
	while (running) {
		// Main loop
		last_time = new_time;
		new_time = glfwGetTime() * 1000000; // Getting time in ns
		unprocessed += new_time - last_time;
		while (unprocessed > time_per_tick) {
            glfwPollEvents();
			update_input(&(cpu->_keys)); // Update input
            cpu_tick(cpu);
			unprocessed -= time_per_tick;
		}
		render(cpu);
		glfwSleep(0.002f);
		running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
	}
}

int main(int argc, char** argv) {
	CHIP_8_CPU *cpu = NULL;

	if (argc < 2) {
		printf("You must send rom file in the arguments\n");
		printf("Example: chipi my_game.rom\n");
		return 1;
	}
    if (strcmp(argv[1], "-d") == 0) { // Disasembler
        if (argc < 3) {
            printf("You must send rom file in the arguments for disasm\n");
            printf("Example: chipi -d my_game.rom\n");
            return 1;
        }
        disasm_rom(argv[2], "disasm.c8");
    } else {
        if (init_io() == RESULT_ERROR) {
            printf("Can't init IO system\n");
            return 1;
        }
        
        cpu = init_cpu(argv[1]);
        
        if (cpu != 0) {
            start_emulation(cpu);
            deinit_io();
            deinit_cpu(cpu);
            cpu = NULL;
        } else {
            printf("Can't init CPU or load rom\n");
            return 1;
        }
    }

	return 0;
}
