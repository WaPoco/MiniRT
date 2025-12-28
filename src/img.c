/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:55:25 by vpogorel          #+#    #+#             */
/*   Updated: 2025/12/24 15:19:01 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int			color;
	t_sphere	sphere;
	t_tuple 	p_light = {10, 10, 0, 0};	
	t_tuple		p_eye;
	t_tuple 	*sphere_points;
	t_tuple 	*plane_points;
	t_plane 	plane_xz = {{0,0,0,0}, {0,1,0,0}, {255,255,255}};

	vector_scale(&p_eye, ray.direction, -1)
	
	plane_points = int_section_plane(ray, plane_xz);
	if (fabs(plane_points[0].x) > 0 && fabs(plane_points[0].z) > 0)
	{
	 	color = lighting(ray.direction, p_light, plane_points[0], p_eye, plane_xz.normal);
		my_mlx_pixel_put(data, x, y, color);
	}
	sphere_points = int_section_sphere(ray, create_tuple(0,0,0) , sphere.radius);
	if (fabs(sphere_points[0].x) > 0 || fabs(sphere_points[0].y) > 0 || fabs(sphere_points[0].z) > 0)
	{
		color = lighting(ray.direction, p_light, sphere_points[0], p_eye, sphere_points[0]);
		my_mlx_pixel_put(data, x, y, color);
	}
	free(sphere_points);
	free(plane_points);
}
