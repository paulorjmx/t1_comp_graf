#include "inc/vertex_array.hpp"

VertexArray::VertexArray(unsigned int quantity)
{
    this->vao = new unsigned int[quantity];
    this->quantity = quantity;
}

int VertexArray::gen_buffer()
{
    int error_code = -1;
    if(this->vao != NULL)
    {
        glGenVertexArrays(this->quantity, this->vao);
        error_code = 0;
    }
    return error_code;
}

int VertexArray::bind_vertex_array(unsigned int position)
{
    int error_code = -1;
    if(this->vao != NULL)
    {
        glBindVertexArray(this->vao[position]);
    }
    return error_code;
}

VertexArray::~VertexArray()
{
    if(this->vao != NULL)
    {
        glDeleteVertexArrays(this->quantity, this->vao);
        delete[] this->vao;
        this->quantity = 0;
    }
}
