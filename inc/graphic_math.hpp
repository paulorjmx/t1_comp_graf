#ifndef GRAPHIC_MATH
    #define GRAPHIC_MATH
        class GraphicMath
        {
            private:
                float transf_matrix[16], angle;

            public:
                GraphicMath();
                void translate_matrix(float x, float y, float z);
                void scale_matrix(float x, float y, float z);
                void rotate_matrix(float x, float y, float z, float velocity);
                void perspective_matrix(float fov, float aspect, float znear);
                void stop_rotate();
                float *get_transf_matrix();
                ~GraphicMath();
        };

#endif
