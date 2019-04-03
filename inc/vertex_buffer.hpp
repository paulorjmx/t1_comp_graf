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
                int gen_buffer();
                int bind_buffer(GLenum target, unsigned int pos);
                int buffer_data(GLenum mode, size_t size, const void *data, GLenum usage);
                unsigned int get_vertex_buffer(unsigned int pos);
                ~VertexBuffer();
        };
#endif
