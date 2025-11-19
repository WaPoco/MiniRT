#include "../Include/miniRT.h"

t_ray ray_for_pixel(t_camera camera, int px, int py)
{
    double xoffset = (px + 0.5) * camera.pixel_size;
    double yoffset = (py + 0.5) * camera.pixel_size;
    double world_x = camera.half_width - xoffset;
    double world_y = camera.half_height - yoffset;

    t_tuple pixel = matrix_mult(inverse_matrix(camera.transform), create_tuple(world_x, world_y, -1));
    t_tuple origin = matrix_mult(inverse_matrix(camera.transform), create_tuple(0, 0, 0));
    t_tuple direction;
    vector_diff(&direction, pixel, origin);
    vector_norm(&direction, direction);

    t_ray r;
    r.origin = origin;
    r.direction = direction;
    return r;
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
}