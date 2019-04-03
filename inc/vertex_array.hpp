#ifndef VERTEX_ARRAY_HPP
    #define VERTEX_ARRAY_HPP
        #include <inc/glad/glad.h>
        #include <iostream>

        class VertexArray
        {
            private:
                unsigned int *vao, quantity;

            public:
                VertexArray(unsigned int quantity = 1);
                int gen_buffer();
                int bind_vertex_array(unsigned int position);
                ~VertexArray();
        };
#endif
