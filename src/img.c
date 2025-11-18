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

void	create_img(t_data *data, t_tuple p, int x, int y)
{
	int		color;
/*
    if (p.imagpart  <= 2 && p.imagpart >= -2 && p.realpart  <= 2 && p.realpart >= -2)
    {
	    color = create_trgb(0, 250, 0, 0);
	    my_mlx_pixel_put(data, x, y, color);
    }
    else
    {
	    color = create_trgb(0, 0, 0, 0);
	    my_mlx_pixel_put(data, x, y, color);
    }

	double alpha = 0;
	while ()
	{
		color = create_trgb(0, 250, 0, 0);

	}
*/
	double radius_sphere = 1;
	t_tuple o_ray = {0, 0, -10, 0};
	t_tuple p_light = {-10, 10, -10, 0};
	t_tuple orgin = {0, 0, 0, 0};
	t_tuple p_eye = {10, 10, 0, 0};
	t_tuple *ray = malloc(sizeof(t_tuple));
	ray->x = 0;
	ray->y = 0;
	ray->z = 0;
	ray->type = 1;
	
	vector_diff(ray, p, o_ray);
	vector_scale(&p_eye, *ray, -1);
	//vector_norm(ray, *ray);
	t_tuple *r_points = int_section(*ray, o_ray, orgin, radius_sphere);
	if (r_points[0].x != 0 && r_points[0].y != 0 && r_points[0].z != 0)
	{
		color = lighting(*ray, p_light, r_points[0], p_eye, r_points[0]);
		//color = create_trgb(0 , (int)color, (int)color, (int)color);
	    my_mlx_pixel_put(data, x, y, color);
	}
	free(ray);
	free(r_points);
}