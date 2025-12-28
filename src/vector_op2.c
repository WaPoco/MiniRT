/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:23:19 by vpogorel          #+#    #+#             */
/*   Updated: 2025/12/28 18:24:09 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

void	vector_norm(t_tuple *result, t_tuple a)
{
	double	factor;
	t_tuple	origin;

	origin.type = 0;
	origin.x = 0.0;
	origin.y = 0.0;
	origin.z = 0.0;
	factor = euclidean_distance(a, origin);
	(*result).x = (1.0 / factor) * a.x;
	(*result).y = (1.0 / factor) * a.y;
	(*result).z = (1.0 / factor) * a.z;
}

void	vector_diff(t_tuple *result, t_tuple a, t_tuple b)
{
	(*result).x = a.x - b.x;
	(*result).y = a.y - b.y;
	(*result).z = a.z - b.z;
}

void	vector_neg(t_tuple *result, t_tuple a)
{
	(*result).x = -a.x;
	(*result).y = -a.y;
	(*result).z = -a.z;
}

void	vector_reflexion(t_tuple *result, t_tuple ray, t_tuple normal)
{
	double	distance_mirror_plane;
	t_tuple	scale_result;

	distance_mirror_plane = 2 * scalar_product(normal, ray);
	vector_scale(&scale_result, normal, distance_mirror_plane);
	vector_diff(result, ray, scale_result);
}

t_tuple	create_tuple(double x, double y, double z)
{
	t_tuple	tuple;

	tuple.x = x;
	tuple.y = y;
	tuple.z = z;
	tuple.type = 1;
	return (tuple);
}

t_tuple	cross_product(t_tuple a, t_tuple b)
{
	t_tuple	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}
