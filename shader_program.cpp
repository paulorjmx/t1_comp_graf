#include "inc/shader_program.hpp"
#include <iostream>

using namespace std;

ShaderProgram::ShaderProgram()
{
    this->shader_program_id = 0;
}

void ShaderProgram::create_shader_program()
{
    this->shader_program_id = glCreateProgram();
}

int ShaderProgram::attach_shader(Shader shader)
{
    int error_code = -1;
    if(this->shader_program_id != -1)
    {
        if(shader.is_compiled())
        {
            glAttachShader(this->shader_program_id, shader.get_shader_id());
            error_code = 0;
        }
        else
        {
            error_code = -2;
        }
    }
    return error_code;
}

void ShaderProgram::link_program()
{
    int sucess = -1;
    glLinkProgram(this->shader_program_id);
    glGetProgramiv(this->shader_program_id, GL_LINK_STATUS, &sucess);
    if(!sucess)
    {
        char info_log[512];
        glGetProgramInfoLog(this->shader_program_id, 512, NULL, info_log);
        cerr << "Program shader error: " << info_log << endl;
    }
}

unsigned int ShaderProgram::get_shader_program_id()
{
    return this->shader_program_id;
}

void ShaderProgram::user_program()
{
    glUseProgram(this->shader_program_id);
}

ShaderProgram::~ShaderProgram()
{
    this->shader_program_id = 0;
}
