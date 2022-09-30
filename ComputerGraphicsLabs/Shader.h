#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    
    GLuint Program;
    
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
   
    void Use();
};