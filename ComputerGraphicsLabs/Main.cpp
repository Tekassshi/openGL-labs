#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Scene.h"
#include "Shader.h"
#include "Window.h"

int main() {

	GLFWwindow* window = getWindow();

	renderScene(window);
	
	glfwTerminate();

	return 0;
}
