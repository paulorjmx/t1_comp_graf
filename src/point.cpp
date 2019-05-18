#include "../inc/point.hpp"

Point::Point()
{
    this->point[0] = 0.0f;
    this->point[1] = 0.0f;
    this->point[2] = 0.0f;
}

Point::Point(const Point &p)
{
    this->point[0] = p.point[0];
    this->point[1] = p.point[1];
    this->point[2] = p.point[2];
}

Point::Point(float x, float y, float z)
{
    this->point[0] = x;
    this->point[1] = y;
    this->point[2] = z;
}

Point Point::operator-(const Point &a)
{
    Point n;
    n.point[0] = this->point[0] - a.point[0];
    n.point[1] = this->point[1] - a.point[1];
    n.point[2] = this->point[2] - a.point[2];
    return n;
}

Point Point::operator+(const Point &a)
{
    Point n;
    n.point[0] = this->point[0] + a.point[0];
    n.point[1] = this->point[1] + a.point[1];
    n.point[2] = this->point[2] + a.point[2];
    return n;
}

void Point::set_point(float x, float y, float z)
{
    this->point[0] = x;
    this->point[1] = y;
    this->point[2] = z;
}

float *Point::get_point()
{
    return this->point;
}

Point::~Point()
{
    this->point[0] = 0.0f;
    this->point[1] = 0.0f;
    this->point[2] = 0.0f;
}
