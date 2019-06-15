#include "../inc/graphic_math.hpp"
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

void GraphicMath::perspective_matrix(float fov, float znear, float zfar)
{
    float half_angle = (fov * 0.5f * M_PI) / 180.0f; // Tranform angle in radians
    float aspect = 4.0f / 3.0f; // Fixed aspect
    float scale = 1.0f / tan(half_angle);

    this->transf_matrix[0] = (aspect * scale);
    this->transf_matrix[1] = 0.0f;
    this->transf_matrix[2] = 0.0f;
    this->transf_matrix[3] = 0.0f;

    this->transf_matrix[4] = 0.0f;
    this->transf_matrix[5] = scale;
    this->transf_matrix[6] = 0.0f;
    this->transf_matrix[7] = 0.0f;

    this->transf_matrix[8] = 0.0f;
    this->transf_matrix[9] = 0.0f;
    this->transf_matrix[10] = (zfar + znear) / (zfar - znear);
    this->transf_matrix[11] = 1.0f;

    this->transf_matrix[12] = 0.0f;
    this->transf_matrix[13] = 0.0f;
    this->transf_matrix[14] = (2.0f * znear * zfar) / (znear - zfar);
    this->transf_matrix[15] = 0.0f;
}

float *GraphicMath::get_transf_matrix()
{
    return this->transf_matrix;
}

void GraphicMath::scale_matrix(float x, float y, float z)
{
    this->transf_matrix[0] = x;
    this->transf_matrix[1] = 0.0f;
    this->transf_matrix[2] = 0.0f;
    this->transf_matrix[3] = 0.0f;

    this->transf_matrix[4] = 0.0f;
    this->transf_matrix[5] = y;
    this->transf_matrix[6] = 0.0f;
    this->transf_matrix[7] = 0.0f;

    this->transf_matrix[8] = 0.0f;
    this->transf_matrix[9] = 0.0f;
    this->transf_matrix[10] = z;
    this->transf_matrix[11] = 0.0f;

    this->transf_matrix[12] = 0.0f;
    this->transf_matrix[13] = 0.0f;
    this->transf_matrix[14] = 0.0f;
    this->transf_matrix[15] = 1.0f;
}

GraphicMath::~GraphicMath()
{

}
