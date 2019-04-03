#ifndef VERTEX_BUFFER_HPP
    #define VERTEX_BUFFER_HPP
        #include <inc/glad/glad.h>
        #include <iostream>

        class VertexBuffer
        {
            private:
                unsigned int *vbo, quantity;

            public:
                VertexBuffer(unsigned int quantity = 1);
                void gen_buffer();
                void bind_buffer(GLenum target, unsigned int pos);
                void buffer_data(GLenum mode, size_t size, const void *data, GLenum usage);
                unsigned int get_vertex_buffer(unsigned int pos);
                ~VertexBuffer();
        };
#endif
