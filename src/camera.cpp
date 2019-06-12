#include "../inc/camera.hpp"
#include "../inc/vec3d.hpp"
#include <iostream>

Camera::Camera(Point ref_point, Point look_at, Vec3D up)
{
    float *forward, *up, *right, *ref_point_coordinates;
    Vec3D zaxis(ref_point, look_at); // Forward vector
    zaxis.normalize();
    Vec3D xaxis = up.cross_product(zaxis); // Right vector
    xaxis.normalize();
    Vec3D yaxis = zaxis.cross_product(xaxis); // Up vector

    forward = zaxis.get_coodinates();
    right = xaxis.get_coodinates();
    up = yaxis.get_coodinates();

    this->view_mat[0] = right[0];
    this->view_mat[1] = up[0];
    this->view_mat[2] = forward[0];
    this->view_mat[3] = 0x0f;

    this->view_mat[4] = right[1];
    this->view_mat[5] = up[1];
    this->view_mat[6] = forward[1];
    this->view_mat[7] = 0x0f;

    this->view_mat[8] = right[2];
    this->view_mat[9] = up[2];
    this->view_mat[10] = forward[2];
    this->view_mat[11] = 0x0f;

    this->view_mat[12] = -1.0f * (xaxis.point_product(ref_point));
    this->view_mat[13] = -1.0f * (yaxis.point_product(ref_point));
    this->view_mat[14] = -1.0f * (zaxis.point_product(ref_point));
    this->view_mat[15] = 1.0f;
}

float *Camera::get_view_matrix()
{
    return this->view_mat;
}

Camera::~Camera()
{

}
