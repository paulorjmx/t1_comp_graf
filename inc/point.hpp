#ifndef POINT_HPP
    #define POINT_HPP
        class Point
        {
            private:
                float point[3];

            public:
                Point();
                Point(const Point &p);
                Point(float x, float y, float z);
                Point operator-(const Point &a);
                Point operator+(const Point &a);
                void set_point(float x, float y, float z);
                float *get_point();
                ~Point();
        };
#endif
