/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 16:04:18 by vpogorel          #+#    #+#             */
/*   Updated: 2026/01/07 19:30:10 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

t_tuple	cross_product(t_tuple a, t_tuple b)
{
	t_tuple	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

void	get_points(t_tuple *p, t_tuple ray, t_tuple o_ray, double d[])
{
	t_tuple	scale_vec;

	vector_scale(&scale_vec, ray, d[0]);
	vector_add(p, o_ray, scale_vec);
}
