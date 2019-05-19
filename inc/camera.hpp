#ifndef CAMERA_HPP
    #define CAMERA_HPP
        #include "point.hpp"

        class Camera
        {
            private:
                float view_mat[16];

            public:
                Camera(Point ref_point, Point look_at);
                float *get_view_matrix();
                ~Camera();
        };
#endif
