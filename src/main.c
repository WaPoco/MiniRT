/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:55:50 by vpogorel          #+#    #+#             */
/*   Updated: 2025/12/10 21:55:52 by vpogorel         ###   ########.fr       */
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

static int	render_next_frame(t_data *data)
{
	//long double	d[2];
	int			i;
	int			k;
	//t_tuple	p;
	t_camera camera;
	t_ray	ray;
	//d[0] = (data->real_max - data->real_min) / data->win_width;
	//d[1] = (data->imag_max - data->imag_min) / data->win_height;

	i = 0;
	camera.hsize = data->win_width;
	camera.vsize = data->win_height;
	camera.field_of_view = 3.1415 / 2.0;
	camera.aspect = camera.hsize / camera.vsize;
	ajust_camera(&camera);
	while (i < data->win_width)
	{
		k = 0;
		while (k < data->win_height)
		{
/*			p.x = data->real_min + camera.pixel_size * i;
			p.y = data->imag_max - camera.pixel_size * k;
			p.z = -1;
			p.type = 1;
*/
			ray = ray_for_pixel(camera, i, k);
			//print ray direction and origin for debugging
			//printf("Ray for pixel (%d, %d): Direction (%f, %f, %f), Origin (%f, %f, %f)\n", i, k, ray.direction.x, ray.direction.y, ray.direction.z, ray.origin.x, ray.origin.y, ray.origin.z);
			create_img(data, ray, i, k);
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
	//error_init_style(&data);
	//show_options(&data, args0, args);
	data.win_height = 500;
	data.win_width = 500;
	data.zoom = 1;
	//data.t = style(&data);
	data.fixated = 0;
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