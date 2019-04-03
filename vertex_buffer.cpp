#include "inc/vertex_buffer.hpp"
#include "inc/opengl_exception.hpp"

VertexBuffer::VertexBuffer(unsigned int quantity)
{
    if(quantity > 0)
    {
        this->vbo = new unsigned int[quantity];
        this->quantity = quantity;
    }
    else
    {
        throw(OpenglException("Quantity need to be greater than 0", 530));
    }
}

void VertexBuffer::gen_buffer()
{
    if(this->vbo != NULL)
    {
        glGenBuffers(this->quantity, this->vbo);
    }
    else
    {
        throw(OpenglException("You need to instantiate the Vertex Buffer class.", 560));
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
        throw(OpenglException("You need to instantiate the Vertex Buffer class.", 560));
    }
}

void VertexBuffer::bind_buffer(GLenum target, unsigned int pos)
{
    if(this->vbo != NULL)
    {
        if(target != GL_ARRAY_BUFFER || target != GL_ATOMIC_COUNTER_BUFFER || target != GL_COPY_READ_BUFFER || target != GL_COPY_WRITE_BUFFER || target != GL_DISPATCH_INDIRECT_BUFFER || target != GL_DRAW_INDIRECT_BUFFER || target != GL_ELEMENT_ARRAY_BUFFER || target != GL_PIXEL_PACK_BUFFER || target != GL_PIXEL_UNPACK_BUFFER || target != GL_QUERY_BUFFER || target != GL_SHADER_STORAGE_BUFFER || target != GL_TEXTURE_BUFFER || target !=  GL_TRANSFORM_FEEDBACK_BUFFER || target != GL_UNIFORM_BUFFER)
        {
            throw(OpenglException("Invalid target", 207));
        }
        else
        {
            glBindBuffer(target, this->vbo[pos]);
        }
    }
    else
    {
        throw(OpenglException("You need to instantiate the Vertex Buffer class.", 590));
    }
}

void VertexBuffer::buffer_data(GLenum mode, size_t size, const void *data, GLenum usage)
{
    if(this->vbo != NULL)
    {
        if(data != NULL)
        {
            if(size > 0)
            {
                if(mode != GL_ARRAY_BUFFER || mode != GL_ATOMIC_COUNTER_BUFFER || mode != GL_COPY_READ_BUFFER || mode != GL_COPY_WRITE_BUFFER || mode != GL_DISPATCH_INDIRECT_BUFFER || mode != GL_DRAW_INDIRECT_BUFFER || mode != GL_ELEMENT_ARRAY_BUFFER || mode != GL_PIXEL_PACK_BUFFER || mode != GL_PIXEL_UNPACK_BUFFER || mode != GL_QUERY_BUFFER || mode != GL_SHADER_STORAGE_BUFFER || mode != GL_TEXTURE_BUFFER || mode !=  GL_TRANSFORM_FEEDBACK_BUFFER || mode != GL_UNIFORM_BUFFER)
                {
                    throw(OpenglException("Invalid mode", 209));
                }
                else
                {
                    if(usage != GL_STREAM_DRAW || usage != GL_STREAM_READ || usage != GL_STREAM_COPY || usage != GL_STATIC_DRAW || usage != GL_STATIC_READ || usage != GL_STATIC_COPY || usage != GL_DYNAMIC_DRAW || usage != GL_DYNAMIC_READ || usage != GL_DYNAMIC_COPY)
                    {
                        throw(OpenglException("Invalid usage", 208));
                    }
                    else
                    {
                        glBufferData(mode, size, data, usage);
                    }
                }
            }
            else
            {
                throw(OpenglException("The data is not empty.", 205));
            }
        }
        else
        {
            throw(OpenglException("The data couldn't be empty.", 200));
        }
    }
    else
    {
        throw(OpenglException("You need to instantiate the Vertex Buffer class.", 590));
    }
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
