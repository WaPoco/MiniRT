#include "../Include/miniRT.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

void	create_img(t_data *data, t_ray ray, int x, int y)
{
	int		color;
	double radius_sphere = 3.0;
	t_tuple o_ray = ray.origin;
	t_tuple p_light = {10, 10, -7, 0};
	t_tuple orgin = {0, 0, 0, 0};
	t_tuple p_eye;
	t_tuple *sphere_points;
	t_tuple *plane_points;
	//t_sphere sphere = {{0,0,0,0}, {255,0,0}, 3.0};
	t_plane plane_xy = {{0,0,0,0}, {1,0,0,0}, {255,255,255}};

	/*t_tuple *ray = malloc(sizeof(t_tuple));
	ray->x = 0;
	ray->y = 0;
	ray->z = 0;
	ray->type = 1;
	*/
	//vector_diff(ray, p, o_ray);
	vector_scale(&p_eye, ray.direction, -1);
	// printf ray direction and origin for debugging and origin
	//printf("Ray Direction at pixel (%d, %d): (%f, %f, %f) and origin (%f,%f,%f)\n", x, y, ray.direction.x, ray.direction.y, ray.direction.z, ray.origin.x, ray.origin.y, ray.origin.z);
	//vector_norm(ray, *ray);
	plane_points = int_section_plane(ray, plane_xy);
	// print plane intersection points for debugging
	//printf("Plane Intersection Points at pixel (%d, %d): Point 1 (%f, %f, %f), Point 2 (%f, %f, %f)\n", x, y, plane_points[0].x, plane_points[0].y, plane_points[0].z, plane_points[1].x, plane_points[1].y, plane_points[1].z);
	if (plane_points[0].x != 0 && plane_points[0].y != 0 && plane_points[0].z != 0)
	{
		color = lighting(ray.direction, p_light, plane_points[0], p_eye, plane_points[0]);
		//color = create_trgb(0 , (int)color, (int)color, (int)color);
	    my_mlx_pixel_put(data, x, y, color);
	}
	sphere_points = int_section_sphere(ray.direction, o_ray, orgin, radius_sphere);
	if (sphere_points[0].x != 0 && sphere_points[0].y != 0 && sphere_points[0].z != 0)
	{
		color = lighting(ray.direction, p_light, sphere_points[0], p_eye, sphere_points[0]);
		//color = create_trgb(0 , (int)color, (int)color, (int)color);
	    my_mlx_pixel_put(data, x, y, color);
	}
//	free(ray);
	free(sphere_points);
}