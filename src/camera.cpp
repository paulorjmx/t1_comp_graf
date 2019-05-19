#include "../inc/camera.hpp"
#include "../inc/vec3d.hpp"
#include <iostream>

Camera::Camera(Point ref_point, Point look_at)
{
    float *zview_coordinates, *u_coordinates, *v_coordinates, *ref_point_coordinates;
    Vec3D zview(ref_point, look_at);
    zview.normalize();
    zview_coordinates = zview.get_coodinates();

    Vec3D u = zview.cross_product(Vec3D(Point(0.0f, 0.0f, 0.0f), Point(0.0f, 1.0f, 0.0f)));
    u.normalize();
    u_coordinates = u.get_coodinates();

    Vec3D v = zview.cross_product(u);
    v_coordinates = v.get_coodinates();

    ref_point_coordinates = ref_point.get_point();

    this->view_mat[0] = u_coordinates[0];
    this->view_mat[1] = v_coordinates[0];
    this->view_mat[2] = zview_coordinates[0];
    this->view_mat[3] = 0.0f;

    this->view_mat[4] = u_coordinates[1];
    this->view_mat[5] = v_coordinates[1];
    this->view_mat[6] = zview_coordinates[1];
    this->view_mat[7] = 0.0f;

    this->view_mat[8] = u_coordinates[2];
    this->view_mat[9] = v_coordinates[2];
    this->view_mat[10] = zview_coordinates[2];
    this->view_mat[11] = 0.0f;

    this->view_mat[12] = ((-1.0f * ref_point_coordinates[0]) * u_coordinates[0]) + ((-1.0f * ref_point_coordinates[1]) * u_coordinates[1]) + ((-1.0f * ref_point_coordinates[2]) * u_coordinates[2]);
    this->view_mat[13] = ((-1.0f * ref_point_coordinates[0]) * v_coordinates[0]) + ((-1.0f * ref_point_coordinates[1]) * v_coordinates[1]) + ((-1.0f * ref_point_coordinates[2]) * v_coordinates[2]);
    this->view_mat[14] = ((-1.0f * ref_point_coordinates[0]) * zview_coordinates[0]) + ((-1.0f * ref_point_coordinates[1]) * zview_coordinates[1]) + ((-1.0f * ref_point_coordinates[2]) * zview_coordinates[2]);
    this->view_mat[15] = 1.0f;

}

float *Camera::get_view_matrix()
{
    return this->view_mat;
}

Camera::~Camera()
{

}
