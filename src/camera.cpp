#include "../inc/camera.hpp"
#include "../inc/vec3d.hpp"
#include <iostream>

Camera::Camera(Point ref_point, Point look_at)
{
    float *forward, *up, *right, *ref_point_coordinates;
    Vec3D n(ref_point, look_at);

    Vec3D tmp(Point(0.0f, 0.0f, 0.0f), Point(0.0f, 1.0f, 0.0f));
    n.normalize();

    Vec3D u = tmp.cross_product(n);
    u.normalize();

    Vec3D v = n.cross_product(u);

    forward = n.get_coodinates();
    right = u.get_coodinates();
    up = v.get_coodinates();
    ref_point_coordinates = ref_point.get_point();

    this->view_mat[0] = right[0];
    this->view_mat[1] = right[1];
    this->view_mat[2] = right[2];
    this->view_mat[3] = 0.0f;

    this->view_mat[4] = up[0];
    this->view_mat[5] = up[1];
    this->view_mat[6] = up[2];
    this->view_mat[7] = 0.0f;

    this->view_mat[8] = forward[0];
    this->view_mat[9] = forward[1];
    this->view_mat[10] = forward[2];
    this->view_mat[11] = 0.0f;

    this->view_mat[12] = ref_point_coordinates[0];
    this->view_mat[13] = ref_point_coordinates[1];
    this->view_mat[14] = ref_point_coordinates[2];
    this->view_mat[15] = 1.0f;

}

float *Camera::get_view_matrix()
{
    return this->view_mat;
}

Camera::~Camera()
{

}
