#ifndef VERTEX_HPP
    #define VERTEX_HPP
        class Vertex
        {
            private:
                float x, y, z;

            public:
                Vertex();
                Vertex(float x, float y, float z);
                void set_x(float x);
                void set_y(float y);
                void set_z(float z);
                float get_x();
                float get_y();
                float get_z();
                ~Vertex();
        };
#endif
