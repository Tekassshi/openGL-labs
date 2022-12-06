#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <SOIL/SOIL.h>;

void renderScene(GLFWwindow* window) {

	// Window dimensions
	const GLuint WIDTH = 1920, HEIGHT = 1080;

	/*			Pyramid			*/

	Shader my_shader("D:\\Other\\C++ Scripts\\ComputerGraphicsLabs\\ComputerGraphicsLabs\\Shader.vert", 
				  "D:\\Other\\C++ Scripts\\ComputerGraphicsLabs\\ComputerGraphicsLabs\\Shader.frag");

	// Pyramid

	GLfloat vertices[] = {

		//front triangle		// Colors
		 0.0f,  0.7f, 0.0f,		0.0f,  1.0f, 1.0f,	// 0
		-1.0f, -1.0f, 1.0f,		0.0f,  1.0f, 1.0f,	// 1
		 1.0f, -1.0f, 1.0f, 	0.0f,  1.0f, 1.0f,	// 2
								
		//right triangle		
		0.0f,  0.7f,  0.0f, 	1.00, 1.00, 0.00,	// 3
		1.0f, -1.0f,  1.0f,		1.00, 1.00, 0.00,	// 4
		1.0f, -1.0f, -1.0f,		1.00, 1.00, 0.00,	// 5
								
		//back triangle			
		 0.0f,  0.7f,  0.0f, 	0.94, 0.00, 1.00,	// 6
		 1.0f, -1.0f, -1.0f,	0.94, 0.00, 1.00,	// 7
		-1.0f, -1.0f, -1.0f,	0.94, 0.00, 1.00,	// 8
								
		//left triangle			
		 0.0f,  0.7f,  0.0f, 	0.00, 0.98, 0.51,	// 9
		-1.0f, -1.0f, -1.0f,	0.00, 0.98, 0.51,	// 10
		-1.0f, -1.0f,  1.0f,	0.00, 0.98, 0.51,	// 11
								
		//bottom triangle		
		-1.0f, -1.0f,  1.0f,	0.0f,  1.0f, 1.0f,	// 12
		 1.0f, -1.0f,  1.0f,	0.0f,  1.0f, 0.63f,	// 13
		-1.0f, -1.0f, -1.0f,	0.59f, 0.0f, 1.0f,	// 14
								
		//bottom triangle right	
		0.0f, 0.0f, -1.0f,		0.0f,  1.0f, 1.0f,	// 15
		0.0f, 0.0f,  0.0f,		0.0f,  1.0f, 0.63f,	// 16
		0.0f, 0.0f,  0.0f,		0.59f, 0.0f, 1.0f,	// 17
	};

	GLuint indices[] = {
		0, 1, 2,	// Triangle 1
		3, 4, 5,	// Triangle 2
		6, 7, 8,	// Triangle 3
		9, 10, 11,	// Triangle 4
		12, 13, 14, // Triangle 5
		15, 16, 17, // Triangle 6
	};

	// Texture

	// Texture atribute

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Set the texture wrapping parameters
	float borderColor[] = {1.0f, 0.0f, 0.0f, 1.0f};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("D:/Other/C++ Scripts/ComputerGraphicsLabs/Obamium/Front.png", &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr) {
		std::cout << "Texture didnt load";
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Generating buffer objects
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	// Copy data from vertices to buffer

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	// Depth buffer
	glEnable(GL_DEPTH_TEST);

	// Gaming loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		my_shader.Use();

		// Draw container
		glBindVertexArray(VAO);

		for (GLuint i = 0; i < 3; i++)
		{

			// Create transformations
			glm::mat4 model = glm::mat4(1);
			glm::mat4 view = glm::mat4(1);
			glm::mat4 projection = glm::ortho(0.0f, 100.0f, 0.0f, 600.0f, 0.1f, 100.0f);
			glm::mat4 transform = glm::mat4(1);

			model = glm::rotate(model, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));

			if (i == 0)
				view = glm::translate(view, glm::vec3(3.0f, -0.2f, -5.5f));
			else if (i == 1)
				view = glm::translate(view, glm::vec3(-3.0f, -0.2f, -5.5f));
			else if (i == 2)
				view = glm::translate(view, glm::vec3(0.0f, -0.2f, -5.5f));

			projection = glm::perspective(45.0f, (GLfloat) WIDTH / (GLfloat) HEIGHT, 0.1f, 100.0f);
			transform = glm::rotate(transform, (GLfloat)glfwGetTime() * 1.2f, glm::vec3(0.0f, 1.0f, 0.0f));

			// Get their uniform location
			GLint modelLoc = glGetUniformLocation(my_shader.Program, "model");
			GLint viewLoc = glGetUniformLocation(my_shader.Program, "view");
			GLint projLoc = glGetUniformLocation(my_shader.Program, "projection");
			GLint transformLoc = glGetUniformLocation(my_shader.Program, "transform");
			//GLint lightPosLoc = glGetUniformLocation(lightingShader.Program, "lightPos");

			// Pass them to the shaders
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
			/*glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);*/

			glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
		}

		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}