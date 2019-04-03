#include "inc/vertex_buffer.hpp"

VertexBuffer::VertexBuffer(unsigned int quantity)
{
    this->vbo = new unsigned int[quantity];
    this->quantity = quantity;
}

int VertexBuffer::gen_buffer()
{
    int error_code = -1;
    if(this->vbo != NULL)
    {
        glGenBuffers(this->quantity, this->vbo);
    }
    return error_code;
}

unsigned int VertexBuffer::get_vertex_buffer(unsigned int pos)
{
    if(this->vbo != NULL)
    {
        return this->vbo[pos];
    }
    else
    {
        return 0;
    }
}

int VertexBuffer::bind_buffer(GLenum target, unsigned int pos)
{
    int error_code = -1;
    if(this->vbo != NULL)
    {
        glBindBuffer(target, this->vbo[pos]);
    }
    return error_code;
}

int VertexBuffer::buffer_data(GLenum mode, size_t size, const void *data, GLenum usage)
{
    int error_code = -1;
    if(this->vbo != NULL)
    {
        glBufferData(mode, size, data, usage);
    }
    return error_code;
}

VertexBuffer::~VertexBuffer()
{
    if(this->vbo != NULL)
    {
        glDeleteBuffers(this->quantity, this->vbo);
        delete[] this->vbo;
        this->quantity = 0;
    }
}
