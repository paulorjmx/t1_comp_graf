#ifndef VEC3D_HPP
    #define VEC3D_HPP
        #include "point.hpp"

        class Vec3D
        {
            private:
                float coordinates[3];

            public:
                Vec3D();
                Vec3D(const Vec3D &u);
                Vec3D(Point a, Point b);
                float *get_coodinates();
                void set_coordinate(float x, float y, float z);
                Vec3D cross_product(Vec3D u);
                void scalar_product(float scalar);
                float dot_product(Vec3D u);
                void normalize();
                ~Vec3D();
        };
#endif
