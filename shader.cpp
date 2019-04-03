#include "inc/shader.hpp"
#include <cstring>
#include <iostream>

using namespace std;

Shader::Shader()
{
    this->shader_id = 0;
    this->shader_type = GL_VERTEX_SHADER;
    this->created = false;
    this->sourced = false;
    this->compiled = false;
}

Shader::Shader(GLenum shader_type)
{
    this->shader_id = 0;
    this->shader_type = shader_type;
    this->created = false;
    this->sourced = false;
    this->compiled = false;
}

void Shader::set_shader_type(GLenum shader_type)
{
    this->shader_type = shader_type;
}

int Shader::set_shader_source(const char **source, unsigned int count)
{
    int error_code = -1;
    if(source != NULL)
    {
        if(count > 0)
        {
            if(this->created)
            {
                glShaderSource(this->shader_id, count, source, NULL);
                this->sourced = true;
            }
            else
            {
                error_code = -3;
            }
        }
        else
        {
            error_code = -2;
        }
    }
    return error_code;
}

unsigned int Shader::get_shader_id()
{
    return this->shader_id;
}

GLenum Shader::get_shader_type()
{
    return this->shader_type;
}

int Shader::create_shader()
{
    int error_code = -1;
    if(this->created != true)
    {
        this->shader_id = glCreateShader(this->shader_type);
        if(this->shader_id != 0)
        {
            error_code = 0;
            this->created = true;
        }
    }
    return error_code;
}

bool Shader::is_created()
{
    return this->created;
}

bool Shader::is_compiled()
{
    return this->compiled;
}

void Shader::compile_shader()
{
    int sucess = -1;
    if(this->sourced)
    {
        glCompileShader(this->shader_id);
        glGetShaderiv(this->shader_id, GL_COMPILE_STATUS, &sucess);
        if(!sucess)
        {
            char info_log[512];
            glGetShaderInfoLog(this->shader_id, 512, NULL, info_log);
            cerr << "Vertex shader error: " << info_log << endl;
        }
        else
        {
            this->compiled = true;
        }
    }
}

Shader::~Shader()
{
    if(this->shader_id != 0)
    {
        glDeleteShader(this->shader_id);
        this->created = false;
    }
    this->shader_id = 0;
    this->shader_type = 0;
    this->sourced = false;
    this->compiled = false;
}
