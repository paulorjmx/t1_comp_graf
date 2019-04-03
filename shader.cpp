#include "inc/shader.hpp"
#include "inc/opengl_exception.hpp"
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
    if(shader_type >= 0)
    {
        this->shader_id = 0;
        this->shader_type = shader_type;
        this->created = false;
        this->sourced = false;
        this->compiled = false;
    }
    else
    {
        throw(OpenglException("Invalid GLenum value", 200));
    }
}

void Shader::set_shader_type(GLenum shader_type)
{
    this->shader_type = shader_type;
}

void Shader::set_shader_source(const char **source, unsigned int count)
{
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
                throw(OpenglException("The shader is need to be created.", 600));
            }
        }
        else
        {
            throw(OpenglException("Count need to be greater than 0.", 200));
        }
    }
    else
    {
        throw(OpenglException("The source code of shader is empty", 200));
    }
}

unsigned int Shader::get_shader_id()
{
    return this->shader_id;
}

GLenum Shader::get_shader_type()
{
    return this->shader_type;
}

void Shader::create_shader()
{
    if(this->created != true)
    {
        this->shader_id = glCreateShader(this->shader_type);
        if(this->shader_id != 0)
        {
            this->created = true;
        }
        else
        {
            throw(OpenglException("Couldn't be possible create the shader.", 150));
        }
    }
    else
    {
        throw(OpenglException("The shader is already created.", 620));
    }
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
            throw(OpenglException(info_log, 810));
        }
        else
        {
            this->compiled = true;
        }
    }
    else
    {
        throw(OpenglException("You need to attach a shader source code.", 630));
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
