#include "inc/shader_program.hpp"
#include "inc/opengl_exception.hpp"
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

void ShaderProgram::attach_shader(Shader shader)
{
    if(this->shader_program_id != 0)
    {
        if(shader.is_compiled())
        {
            glAttachShader(this->shader_program_id, shader.get_shader_id());
        }
        else
        {
            throw(OpenglException("You need to compile a shader program first.", 510));
        }
    }
    else
    {
        throw(OpenglException("You need to create a shader program first.", 500));
    }
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
        throw(OpenglException(info_log, 800));
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
