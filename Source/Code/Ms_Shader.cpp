#include "Ms_Shader.h"
#include <fstream>
#include <cstdlib>
#include <cstring>

Ms_Shader::Ms_Shader()
{

}

void Ms_Shader::Load_Shader(std::string File)
{
    std::string Type = ".vert";
    std::string Location = Ms_Shader::String_Join(File, Type);
    std::string vertexShaderSource;
	std::ifstream VertexShaderStream(Location, std::ios::in);


	if(VertexShaderStream.is_open())
        {
            std::string Line = "";
            while(getline(VertexShaderStream, Line))
                vertexShaderSource += "\n" + Line;
            VertexShaderStream.close();
        }
	else
        {
            printf("Impossible to open Shader.!\n");
            getchar();
            exit(0);
        }

    Type = ".frag";
    Location = Ms_Shader::String_Join(File, Type);
	std::string FragmentShaderSource;
	std::ifstream FragmentShaderStream(Location, std::ios::in);

	if(FragmentShaderStream.is_open())
        {
            std::string Line = "";
            while(getline(FragmentShaderStream, Line))
                FragmentShaderSource += "\n" + Line;
            FragmentShaderStream.close();
        }
	else
        {
            printf("Impossible to open shader.!\n");
            getchar();
            exit(0);
        }

    //make vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    char const * VertexSourcePointer = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &VertexSourcePointer, NULL);
    glCompileShader(vertexShader);

    // Check for compile time errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

    // Fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    char const * FragmentSourcePointer = FragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &FragmentSourcePointer, NULL);
    glCompileShader(fragmentShader);

    // Check for compile time errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        // Link shaders
    Ms_Shader::ReadyShader = glCreateProgram();
    glAttachShader(Ms_Shader::ReadyShader, vertexShader);
    glAttachShader(Ms_Shader::ReadyShader, fragmentShader);
    glLinkProgram(Ms_Shader::ReadyShader);
            // Check for linking errors
    glGetProgramiv(Ms_Shader::ReadyShader, GL_LINK_STATUS, &success);
    if (!success)
        {
            glGetProgramInfoLog(Ms_Shader::ReadyShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

std::string Ms_Shader::String_Join(std::string File, std::string Type)
{
    std::string Joined = "Data/Shader/";
    Joined += File;
    Joined += Type;
    return Joined;
}

