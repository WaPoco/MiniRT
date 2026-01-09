/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 15:30:01 by vpogorel          #+#    #+#             */
/*   Updated: 2026/01/09 15:31:06 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

int	render_next_frame(t_data *data)
{
	int			i;
	int			k;
	t_hit		hit;
	t_color		color;
	t_ray		ray;

	i = 0;
	ajust_camera(data);
	while (i < data->win_width)
	{
		k = 0;
		while (k < data->win_height)
		{
			ray = ray_for_pixel(data->world->camera, i, k);
			//printf("direction=(%f, %f, %f) \n", ray.direction.x, ray.direction.y, ray.direction.z);
			if (intersect_world(data->world, ray, &hit))
				color = hit_color(data->world, &ray, &hit);
			else
				color = data->world->ambient.color;
			my_mlx_pixel_put(data, i, k, color_to_trgb(color));
			//create_img(data, ray, i, k);
			k++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
/*	t_sphere *s = data->world->objects->shape;
	s->center.x += 2.0;
	s->center.z += 2.0;
	s->center.y += 2.0;*/
	return (0);
}
