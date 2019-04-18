#include "../inc/vertex_array.hpp"
#include "../inc/opengl_exception.hpp"

VertexArray::VertexArray(unsigned int quantity)
{
    if(quantity > 0)
    {
        this->vao = new unsigned int[quantity];
        this->quantity = quantity;
    }
    else
    {
        throw(OpenglException("Quantity need to be greater than 0", 530));
    }
}

void VertexArray::gen_buffer()
{
    if(this->vao != NULL)
    {
        glGenVertexArrays(this->quantity, this->vao);
    }
    else
    {
        throw(OpenglException("You need to instantiate the Vertex Array class.", 590));
    }
}

void VertexArray::bind_vertex_array(unsigned int position)
{
    if(this->vao != NULL)
    {
        glBindVertexArray(this->vao[position]);
    }
    else
    {
        throw(OpenglException("You need to instantiate the Vertex Array class.", 590));
    }
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
