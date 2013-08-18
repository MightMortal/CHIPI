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

#include "io.h"

#include <GL/glfw.h>

int init_render();
void deinit_render();

int init_io() {
  int err;
  err = init_render();
  if (err != RESULT_SUCCESSFUL) {
    return RESULT_ERROR;
  }
  return RESULT_SUCCESSFUL;
}

void deinit_io() {
  deinit_render();
}

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

void deinit_render() {
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

void update_input(WORD* keys) {
  *keys = 255;
  if (glfwGetKey('1'))
    *keys = 0x1;
  else if (glfwGetKey('2'))
    *keys = 0x2;
  else if (glfwGetKey('3'))
    *keys = 0x3;
  else if (glfwGetKey('Q'))
    *keys = 0x4;
  else if (glfwGetKey('W'))
    *keys = 0x5;
  else if (glfwGetKey('E'))
    *keys = 0x6;
  else if (glfwGetKey('A'))
    *keys = 0x7;
  else if (glfwGetKey('S'))
    *keys = 0x8;
  else if (glfwGetKey('D'))
    *keys = 0x9;
  else if (glfwGetKey('X'))
    *keys = 0x0;
  else if (glfwGetKey('Z'))
    *keys = 0xA;
  else if (glfwGetKey('C'))
    *keys = 0xB;
  else if (glfwGetKey('4'))
    *keys = 0xC;
  else if (glfwGetKey('R'))
    *keys = 0xD;
  else if (glfwGetKey('F'))
    *keys = 0xE;
  else if (glfwGetKey('V'))
    *keys = 0xF;
}
