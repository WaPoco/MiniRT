#include "../Include/miniRT.h"

t_ray ray_for_pixel(t_camera camera, int px, int py)
{
    double xoffset = (px + 0.5) * camera.pixel_size;
    double yoffset = (py + 0.5) * camera.pixel_size;
    double world_x = camera.half_width - xoffset;
    double world_y = camera.half_height - yoffset;
    // print world_x and world_y
    //printf("World Coordinates (%d, %d): (%f, %f)\n", px, py, world_x, world_y);
    t_tuple pixel = matrix_mult(inverse_matrix(camera.transform), create_tuple(world_x, world_y, -1));
    // print the pixel coordinates for debugging
    // printf("Pixel Coordinates (%d, %d): (%f, %f, %f)\n", px, py, pixel.x, pixel.y, pixel.z);
    t_tuple origin = matrix_mult(inverse_matrix(camera.transform), create_tuple(0, 0, 0));
    // print the origin coordinates for debugging
    //printf("Origin Coordinates: (%f, %f, %f)\n", origin.x, origin.y, origin.z);
    t_tuple direction;
    vector_diff(&direction, pixel, origin);
    vector_norm(&direction, direction);

    t_ray r;
    r.origin = origin;
    r.direction = direction;
    return r;
}

double **view_transform(t_tuple from, t_tuple to, t_tuple up)
{
    t_tuple forward;
    vector_diff(&forward, to, from);
    vector_norm(&forward, forward);

    t_tuple upn;
    vector_norm(&upn, up);

    t_tuple left = cross_product(forward, upn);
    // print left vector for debugging
    //printf("Left Vector: (%f, %f, %f)\n", left.x, left.y, left.z);
    // print forward vector for debugging
    //printf("Forward Vector: (%f, %f, %f)\n", forward.x, forward.y, forward.z);
    // print upn vector for debugging
    //printf("Up Vector: (%f, %f, %f)\n", upn.x, upn.y, upn.z);
    t_tuple true_up = cross_product(left, forward);

    double **orientation = allocate_4x4_matrix();
    orientation[0][0] = left.x;     orientation[0][1] = left.y;     orientation[0][2] = left.z;     orientation[0][3] = 0;
    orientation[1][0] = true_up.x;  orientation[1][1] = true_up.y;  orientation[1][2] = true_up.z;  orientation[1][3] = 0;
    orientation[2][0] = -forward.x; orientation[2][1] = -forward.y; orientation[2][2] = -forward.z; orientation[2][3] = 0;
    orientation[3][0] = 0;          orientation[3][1] = 0;          orientation[3][2] = 0;          orientation[3][3] = 1;

    double **translation = translation_matrix(-from.x, -from.y, -from.z);
    // print the orientation and translation matrices for debugging
    /*printf("Orientation Matrix:\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%f ", orientation[i][j]);
        }
        printf("\n");
    }
    printf("Translation Matrix:\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {           printf("%f ", translation[i][j]);
        }
        printf("\n");
    }*/
    double **result = matrix_mult_4x4(orientation, translation);
    // print result matrix for debugging
    /*printf("View Transform Matrix:\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%f ", result[i][j]);
        }
        printf("\n");
    }*/
    free_4x4_matrix(orientation);
    free_4x4_matrix(translation);

    return result;
}

double **translation_matrix(double x, double y, double z)
{
    double **matrix = allocate_4x4_matrix();
    matrix[0][0] = 1; matrix[0][1] = 0; matrix[0][2] = 0; matrix[0][3] = x;
    matrix[1][0] = 0; matrix[1][1] = 1; matrix[1][2] = 0; matrix[1][3] = y;
    matrix[2][0] = 0; matrix[2][1] = 0; matrix[2][2] = 1; matrix[2][3] = z;
    matrix[3][0] = 0; matrix[3][1] = 0; matrix[3][2] = 0; matrix[3][3] = 1;
    return matrix;
}

void    ajust_camera(t_camera *camera)
{
    double half_view = tan(camera->field_of_view / 2);
    if (camera->aspect >= 1)
    {
        camera->half_width = half_view;
        camera->half_height = half_view / camera->aspect;
    }
    else
    {
        camera->half_width = half_view * camera->aspect;
        camera->half_height = half_view;
    }
    camera->pixel_size = (camera->half_width * 2) / camera->hsize;
    t_tuple from = create_tuple(8, 8, 8);
    t_tuple to = create_tuple(1, 1, 1);
    t_tuple up = create_tuple(0, 1, 0);
    camera->transform = view_transform(from, to, up);
    // print the camera transform matrix for debugging
    /*printf("Camera Transform Matrix:\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%f ", camera->transform[i][j]);
        }
        printf("\n");
    }*/
}

