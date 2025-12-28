/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:56:05 by vpogorel          #+#    #+#             */
/*   Updated: 2025/12/28 18:23:46 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

double	scalar_product(t_tuple a, t_tuple b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double	euclidean_distance(t_tuple a, t_tuple b)
{
	return (sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)
			+ (a.z - b.z) * (a.z - b.z)));
}

double	sq_euclidean_distance(t_tuple a, t_tuple b)
{
	return ((a.x - b.x) * (a.x - b.x)
		+ (a.y - b.y) * (a.y - b.y)
		+ (a.z - b.z) * (a.z - b.z));
}

void	vector_add(t_tuple *result, t_tuple a, t_tuple b)
{
	(*result).x = a.x + b.x;
	(*result).y = a.y + b.y;
	(*result).z = a.z + b.z;
}

void	vector_scale(t_tuple *result, t_tuple a, double factor)
{
	(*result).x = factor * a.x;
	(*result).y = factor * a.y;
	(*result).z = factor * a.z;
}
