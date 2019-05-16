#include "../inc/vertex.hpp"

Vertex::Vertex()
{
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
}

Vertex::Vertex(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vertex::set_x(float x)
{
    this->x = x;
}

void Vertex::set_y(float y)
{
    this->y = y;
}

void Vertex::set_z(float z)
{
    this->z = z;
}

float Vertex::get_x()
{
    return this->x;
}

float Vertex::get_y()
{
    return this->y;
}

float Vertex::get_z()
{
    return this->z;
}

Vertex::~Vertex()
{
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
}
