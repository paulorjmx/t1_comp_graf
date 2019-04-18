#include "../inc/shader_source.hpp"
#include "../inc/opengl_exception.hpp"

ShaderSource::ShaderSource()
{
    this->source_code = NULL;
}

ShaderSource::ShaderSource(const char *source)
{
    if(source != NULL)
    {
        this->source_code = (char *) source;
    }
    else
    {
        throw(OpenglException("Source code empty", 200));
    }
}

void ShaderSource::set_shader_source(const char *source)
{
    if(source != NULL)
    {
        this->source_code = (char *) source;
    }
    else
    {
        throw(OpenglException("Source code empty", 200));
    }
}

void ShaderSource::set_shader_source_from_file(const char *filename)
{
    if(filename != NULL)
    {
        if(this->source_code == NULL)
        {
            fstream input_file(filename, ios::in);
            if(input_file.is_open() != true)
            {
                throw(OpenglException("Failed to open the file.", 100));
            }
            else
            {
                input_file.seekg(0, input_file.end);
                unsigned int lenght = input_file.tellg();
                this->source_code = new char[lenght];
                input_file.seekg(0, input_file.beg);
                if(!input_file.read(this->source_code, lenght))
                {
                    throw(OpenglException("An error occured on read the shader source file.", 110));
                }

            }
            input_file.close();
        }
        else
        {
            throw(OpenglException("The shader source code is not empty.", 220));
        }
    }
    else
    {
        throw(OpenglException("The shader file name is empty.", 200));
    }
}

const char *ShaderSource::get_shader_source()
{
    return this->source_code;
}

ShaderSource::~ShaderSource()
{
    delete[] this->source_code;
}
