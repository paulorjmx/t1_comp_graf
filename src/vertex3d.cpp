#include "../inc/vertex.hpp"

Vertex3D::Vertex3D()
{
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
    this->w = 1.0;
}

Vertex3D::Vertex3D(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = 1.0;
}

void Vertex3D::set_coordinates(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

float Vertex3D::get_x()
{
    return this->x;
}

float Vertex3D::get_y()
{
    return this->y;
}

float Vertex3D::get_z()
{
    return this->z;
}

Vertex3D::~Vertex3D()
{
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
    this->w = 1.0;
}
