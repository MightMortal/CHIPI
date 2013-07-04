#include "include/render.h"
#include "include/main.h"
#include "include/GL/glfw.h"
/*
 * Render for CHIP-8 emulator
 * Implementation
 * Author: MightMortal
 */

int init_render() {
	glfwInit();
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	if (glfwOpenWindow(640, 320, 0, 0, 0, 0, 0, 0, GLFW_WINDOW) != GL_TRUE) {
		glfwTerminate();
		return RESULT_ERROR;
	}
	glfwSetWindowTitle("CHIPI");

	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 64, 32, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	return RESULT_SUCCESSFUL;
}

void exit_render() {
	glfwCloseWindow();
	glfwTerminate();
}

void render(CHIP_8_CPU* cpu) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {
			if (cpu->_vram[x][y])
				glColor3f(0x10, 0xFF, 0x10);
			else
				continue;
			glBegin(GL_QUADS);
			glVertex2i(x, y);
			glVertex2i(x + 1, y);
			glVertex2i(x + 1, y + 1);
			glVertex2i(x, y + 1);
			glEnd();
		}
	}
	glfwSwapBuffers();
}
