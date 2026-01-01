/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:55:50 by vpogorel          #+#    #+#             */
/*   Updated: 2025/12/31 16:02:29 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

t_color	background_color(void)
{
	t_color	c;

	c.r = 0.0;
	c.g = 0.0;
	c.b = 0.0;
	return (c);
}

t_color	hit_color(t_world *world, t_ray *ray, t_hit *hit)
{
	t_tuple	p_eye;

	vector_scale(&p_eye, ray->direction, -1);
	hit->obj->mat.color = lighting(world, ray, hit, p_eye);
	return (hit->obj->mat.color);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (printf("Usage: ./miniRT <scene.rt>\n"), 1);
	if (init_data(&data))
		return (printf("Error: memory allocation failed\n"), 1);
	if (!parse_scene(argv[1], data.world))
		return (printf("Error: invalid .rt file\n"), 1);
	mlx_hook(data.win, 17, 1L << 17, close_window, &data);
	mlx_loop_hook(data.mlx, render_next_frame, &data);
	mlx_loop(data.mlx);
	return (0);
}
