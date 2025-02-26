#include <iostream>
// GLEW
#include "glad.h"
// GLFW
#include <GLFW/glfw3.h>
//Math
#include <glm/glm.hpp>

#include <fstream>



class Ms_Shader
{
    public:
        GLuint ReadyShader;

        Ms_Shader();
        void Load_Shader(std::string File);
        std::string String_Join(std::string File, std::string Type);
};

