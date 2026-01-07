/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 21:50:32 by vpogorel          #+#    #+#             */
/*   Updated: 2026/01/07 20:06:07 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

t_ray	ray_for_pixel(t_camera camera, int px, int py)
{
	double	xoffset;
	double	yoffset;
	double	world_x;
	double	world_y;
	t_tuple	pixel;
	t_tuple	origin;
	t_tuple	direction;
	t_ray	r;
	double	**inv;

	//printf("matrix\n");
	/*for(int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%f ", camera.transform[i][j]);
		}
		printf("\n");
	}
	printf("\npx=%d py=%d\n", px, py);
	printf("Inv matrix\n");
	*/
	inv = inverse_matrix(camera.transform);
	/*for(int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%f ", inv[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	double **I = matrix_mult_4x4(camera.transform,  inv);
	for(int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%f ", I[i][j]);
		}
		printf("\n");
	}*/
	xoffset = (px + 0.5) * camera.pixel_size;
	yoffset = (py + 0.5) * camera.pixel_size;
	world_x = camera.half_width - xoffset;
	world_y = camera.half_height - yoffset;
	pixel = matrix_mult(inv, create_tuple(world_x, world_y, 1));
	origin = matrix_mult(inv, create_tuple(0, 0, 0));
	//printf("origin x=%f y=%f z=%f\n", origin.x, origin.y, origin.z);
	vector_diff(&direction, pixel, origin);
	vector_norm(&direction, direction);
	r.origin = origin;
	r.direction = direction;
	free_nxn_matrix(inv, 4);
	return (r);
}

void	set_orientation_matrix(double **orientation, t_tuple left,
		t_tuple true_up, t_tuple forward)
{
	orientation[0][0] = left.x;
	orientation[0][1] = left.y;
	orientation[0][2] = left.z;
	orientation[0][3] = 0;
	orientation[1][0] = true_up.x;
	orientation[1][1] = true_up.y;
	orientation[1][2] = true_up.z;
	orientation[1][3] = 0;
	orientation[2][0] = forward.x;
	orientation[2][1] = forward.y;
	orientation[2][2] = forward.z;
	orientation[2][3] = 0;
	orientation[3][0] = 0;
	orientation[3][1] = 0;
	orientation[3][2] = 0;
	orientation[3][3] = 1;
}

double	**view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple	forward;
	t_tuple	upn;
	t_tuple	left;
	t_tuple	true_up;
	double	**orientation;
	double	**translation;
	double	**result;

	vector_diff(&forward, to, from);
	vector_norm(&forward, forward);
	vector_norm(&upn, up);
	left = cross_product(forward, upn);
	true_up = cross_product(left, forward);
	orientation = allocate_4x4_matrix();
	set_orientation_matrix(orientation, left, true_up, forward);
	translation = translation_matrix(-from.x, -from.y, -from.z);
	result = matrix_mult_4x4(orientation, translation);
	free_nxn_matrix(orientation, 4);
	free_nxn_matrix(translation, 4);
	return (result);
}

double	**translation_matrix(double x, double y, double z)
{
	double	**matrix;

	matrix = allocate_4x4_matrix();
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[0][3] = x;
	matrix[1][0] = 0;
	matrix[1][1] = 1;
	matrix[1][2] = 0;
	matrix[1][3] = y;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
	matrix[2][3] = z;
	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[3][3] = 1;
	return (matrix);
}

void	ajust_camera(t_data *data)
{
	double	half_view;

	data->world->camera.hsize = data->win_width;
	data->world->camera.vsize = data->win_height;
	data->world->camera.aspect = data->world->camera.hsize
		/ data->world->camera.vsize;
	half_view = tan(data->world->camera.field_of_view / 2);
	if (data->world->camera.aspect >= 1)
	{
		data->world->camera.half_width = half_view;
		data->world->camera.half_height = half_view
			/ data->world->camera.aspect;
	}
	else
	{
		data->world->camera.half_width = half_view * data->world->camera.aspect;
		data->world->camera.half_height = half_view;
	}
	data->world->camera.pixel_size = (data->world->camera.half_width * 2)
		/ data->world->camera.hsize;
	data->world->camera.transform = view_transform(data->world->camera.from,
			data->world->camera.to, data->world->camera.up);
	/*printf("up x=%f y=%f z=%f\n", data->world->camera.up.x, data->world->camera.up.y, data->world->camera.up.z);
	printf("from x=%f y=%f z=%f\n", data->world->camera.from.x, data->world->camera.from.y, data->world->camera.from.z);
	printf("to x=%f y=%f z=%f\n", data->world->camera.to.x, data->world->camera.to.y, data->world->camera.to.z);
	//print the matrix
	for(int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%f ", data->world->camera.transform[i][j]);
		}
		printf("\n");
	}*/
}
