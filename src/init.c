/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 15:34:44 by vpogorel          #+#    #+#             */
/*   Updated: 2025/12/31 16:02:07 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

int	init_data(t_data *data)
{
	data->world = malloc(sizeof(t_world));
	if (!data->world)
		return (1);
	data->world->ambient.is_set = 0;
	data->world->camera.is_set = 0;
	data->world->light.is_set = 0;
	data->world->object_count = 0;
	data->win_height = 500;
	data->win_width = 500;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->win_width, data->win_height,
			"MiniRT");
	data->img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	return (0);
}

void	init_scene(t_world *scene)
{
	scene->ambient.is_set = 0;
	scene->camera.is_set = 0;
	scene->light.is_set = 0;
	scene->object_count = 0;
	scene->objects = NULL;
}

int	validate_scene(t_world *scene)
{
	if (!scene->ambient.is_set)
		return (0);
	if (!scene->camera.is_set)
		return (0);
	if (!scene->light.is_set)
		return (0);
	if (!scene->objects)
		return (0);
	return (1);
}
