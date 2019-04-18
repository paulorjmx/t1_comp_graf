#include "inc/graphic_math.hpp"
#include <cmath>
#include <GLFW/glfw3.h>

GraphicMath::GraphicMath()
{
    this->transf_matrix[0] = 1.0f;
    this->transf_matrix[1] = 0.0f;
    this->transf_matrix[2] = 0.0f;
    this->transf_matrix[3] = 0.0f;

    this->transf_matrix[4] = 0.0f;
    this->transf_matrix[5] = 1.0f;
    this->transf_matrix[6] = 0.0f;
    this->transf_matrix[7] = 0.0f;

    this->transf_matrix[8] = 0.0f;
    this->transf_matrix[9] = 0.0f;
    this->transf_matrix[10] = 1.0f;
    this->transf_matrix[11] = 0.0f;

    this->transf_matrix[12] = 0.0f;
    this->transf_matrix[13] = 0.0f;
    this->transf_matrix[14] = 0.0f;
    this->transf_matrix[15] = 1.0f;

    this->angle = (M_PI / 100.0f);
}

void GraphicMath::translate_matrix(float x, float y, float z)
{
    this->transf_matrix[0] = this->transf_matrix[0];
    this->transf_matrix[1] = this->transf_matrix[1];
    this->transf_matrix[2] = this->transf_matrix[2];
    this->transf_matrix[3] = this->transf_matrix[3];

    this->transf_matrix[4] = this->transf_matrix[4];
    this->transf_matrix[5] = this->transf_matrix[5];
    this->transf_matrix[6] = this->transf_matrix[6];
    this->transf_matrix[7] = this->transf_matrix[7];

    this->transf_matrix[8] = this->transf_matrix[8];
    this->transf_matrix[9] = this->transf_matrix[9];
    this->transf_matrix[10] = this->transf_matrix[10];
    this->transf_matrix[11] = this->transf_matrix[11];

    this->transf_matrix[12] += x;
    this->transf_matrix[13] += y;
    this->transf_matrix[14] += z;
    this->transf_matrix[15] = 1.0f;
}

void GraphicMath::rotate_matrix(float x, float y, float z, float velocity)
{
    if(this->angle >= (2.0f * M_PI))
    {
        this->angle = M_PI / 100.0f;
    }
    this->angle += (M_PI / 100.0f) + velocity;
    this->transf_matrix[0] = cos(this->angle);
    this->transf_matrix[1] = sin(this->angle);
    this->transf_matrix[2] = this->transf_matrix[2];
    this->transf_matrix[3] = this->transf_matrix[3];

    this->transf_matrix[4] = -sin(this->angle);
    this->transf_matrix[5] = cos(this->angle);
    this->transf_matrix[6] = this->transf_matrix[6];
    this->transf_matrix[7] = this->transf_matrix[7];

    this->transf_matrix[8] = this->transf_matrix[8];
    this->transf_matrix[9] = this->transf_matrix[9];
    this->transf_matrix[10] = this->transf_matrix[10];
    this->transf_matrix[11] = this->transf_matrix[11];

    this->transf_matrix[12] = this->transf_matrix[12];
    this->transf_matrix[13] = this->transf_matrix[13];
    this->transf_matrix[14] = this->transf_matrix[14];
    this->transf_matrix[15] = 1.0f;
}

void GraphicMath::stop_rotate()
{
    this->transf_matrix[0] = this->transf_matrix[0];
    this->transf_matrix[1] = this->transf_matrix[1];
    this->transf_matrix[2] = this->transf_matrix[2];
    this->transf_matrix[3] = this->transf_matrix[3];

    this->transf_matrix[4] = this->transf_matrix[4];
    this->transf_matrix[5] = this->transf_matrix[5];
    this->transf_matrix[6] = this->transf_matrix[6];
    this->transf_matrix[7] = this->transf_matrix[7];

    this->transf_matrix[8] = this->transf_matrix[8];
    this->transf_matrix[9] = this->transf_matrix[9];
    this->transf_matrix[10] = this->transf_matrix[10];
    this->transf_matrix[11] = this->transf_matrix[11];

    this->transf_matrix[12] = this->transf_matrix[12];
    this->transf_matrix[13] = this->transf_matrix[13];
    this->transf_matrix[14] = this->transf_matrix[14];
    this->transf_matrix[15] = this->transf_matrix[15];
}

float *GraphicMath::get_transf_matrix()
{
    return this->transf_matrix;
}

GraphicMath::~GraphicMath()
{

}
