/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:55:50 by vpogorel          #+#    #+#             */
/*   Updated: 2025/12/28 18:01:51 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_display(data->mlx);
	exit(1);
	return (0);
}

static t_color	background_color(void)
{
	t_color	c;

	c.r = 0.0;
	c.g = 0.0;
	c.b = 0.0;
	return (c);
}

static t_color	hit_color(t_world *world, t_ray *ray, t_hit *hit)
{
	t_tuple	p_eye;

	vector_scale(&p_eye, ray->direction, -1);
	hit->obj->mat.color = lighting(world, ray, hit, p_eye);
	return (hit->obj->mat.color);
}

static int	render_next_frame(t_data *data)
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
			if (intersect_world(data->world, ray, &hit))
				color = hit_color(data->world, &ray, &hit);
			else
				color = background_color();
			my_mlx_pixel_put(data, i, k, color_to_trgb(color));
			//create_img(data, ray, i, k);
			k++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int	main(int args0, char **args)
{
	t_data	data;

	(void)args0;
	(void)args;
	data.win_height = 500;
	data.win_width = 500;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.win_width, data.win_height,
			"MiniRT");
	data.img = mlx_new_image(data.mlx, data.win_width, data.win_height);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	//mlx_hook(data.win, 2, 1L << 0, key_press, &data);
	//mlx_hook(data.win, 4, 1L << 2, mouse_click, &data);
	mlx_hook(data.win, 17, 1L << 17, close_window, &data);
	mlx_loop_hook(data.mlx, render_next_frame, &data);
	mlx_loop(data.mlx);
	return (0);
}
