#include "../inc/vec3d.hpp"
#include <cmath>

Vec3D::Vec3D()
{
    this->coordinates[0] = 0.0f;
    this->coordinates[1] = 0.0f;
    this->coordinates[2] = 0.0f;
}

Vec3D::Vec3D(const Vec3D &u)
{
    this->coordinates[0] = u.coordinates[0];
    this->coordinates[1] = u.coordinates[1];
    this->coordinates[2] = u.coordinates[2];
}

Vec3D::Vec3D(Point a, Point b)
{
    Point c = b - a;
    float *temp = c.get_point();
    this->coordinates[0] = temp[0];
    this->coordinates[1] = temp[1];
    this->coordinates[2] = temp[2];
}

float Vec3D::point_product(Point p)
{
    float *p_coordinates = p.get_point();
    float result = this->coordinates[0] * p_coordinates[0];
    result += this->coordinates[1] * p_coordinates[1];
    result += this->coordinates[2] * p_coordinates[2];
    return result;
}

float *Vec3D::get_coodinates()
{
    return this->coordinates;
}

void Vec3D::set_coordinate(float x, float y, float z)
{
    this->coordinates[0] = x;
    this->coordinates[1] = y;
    this->coordinates[2] = z;
}

Vec3D Vec3D::cross_product(Vec3D u)
{
    Vec3D orth;
    orth.coordinates[0] = (this->coordinates[1] * u.coordinates[2]) - (this->coordinates[2] * u.coordinates[1]);
    orth.coordinates[1] = (this->coordinates[2] * u.coordinates[0]) - (this->coordinates[0] * u.coordinates[2]);
    orth.coordinates[2] = (this->coordinates[0] * u.coordinates[1]) - (this->coordinates[1] * u.coordinates[0]);
    return orth;
}

void Vec3D::scalar_product(float scalar)
{
    this->coordinates[0] = this->coordinates[0] * scalar;
    this->coordinates[1] = this->coordinates[1] * scalar;
    this->coordinates[2] = this->coordinates[2] * scalar;
}

float Vec3D::dot_product(Vec3D u)
{
    float result = 0.0f;
    result += this->coordinates[0] * u.coordinates[0];
    result += this->coordinates[1] * u.coordinates[1];
    result += this->coordinates[2] * u.coordinates[2];
    return result;
}

void Vec3D::normalize()
{
    float norm = 0.0f;
    norm = (float) sqrt((this->coordinates[0] * this->coordinates[0]) + (this->coordinates[1] * this->coordinates[1]) + (this->coordinates[2] * this->coordinates[2]));
    this->coordinates[0] = this->coordinates[0] / norm;
    this->coordinates[1] = this->coordinates[1] / norm;
    this->coordinates[2] = this->coordinates[2] / norm;
}

Vec3D::~Vec3D()
{
    this->coordinates[0] = 0.0f;
    this->coordinates[1] = 0.0f;
    this->coordinates[2] = 0.0f;
}
