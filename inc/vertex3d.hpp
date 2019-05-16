#ifndef VERTEX3D_HPP
    #define VERTEX3D_HPP
        class Vertex3D
        {
            private:
                float x, y, z, w;

            public:
                Vertex3D();
                Vertex3D(float x, float y, float z);
                void set_coordinates(float x, float y, float z);
                float get_x();
                float get_y();
                float get_z();
                ~Vertex3D();
        };
#endif
