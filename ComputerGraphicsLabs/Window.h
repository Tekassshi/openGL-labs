#pragma once

#ifndef WINDOW
#define WINDOW

#include <GLFW/glfw3.h>

GLFWwindow* getWindow();

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

#endif