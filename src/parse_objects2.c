/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 15:35:54 by vpogorel          #+#    #+#             */
/*   Updated: 2026/01/02 15:59:17 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

int	parse_cylinder(char **t, t_world *scene)
{
	t_cylinder	*cylinder;
	t_object	*obj;
	t_tuple		center;
	t_tuple		axis;
	t_tuple		tmp;
	double		diameter;
	double		height;
	t_color		color;

	if (!t[1] || !t[2] || !t[3] || !t[4] || !t[5] || t[6])
		return (0);
	if (!parse_tuple(t[1], &center) || !parse_tuple(t[2], &axis))
		return (0);
	if (axis.x < -1.0 || axis.x > 1.0
		|| axis.y < -1.0 || axis.y > 1.0
		|| axis.z < -1.0 || axis.z > 1.0)
		return (0);
	if (!parse_double(t[3], &diameter) || diameter <= 0.0
		|| !parse_double(t[4], &height) || height <= 0.0
		|| !parse_color(t[5], &color))
		return (0);
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (0);
	cylinder->center = center;
	cylinder->axis = axis;
	cylinder->radius = diameter / 2.0;
	cylinder->height = height;
	cylinder->color = color;
	vector_scale(&tmp, axis, height / 2);
	vector_diff(&cylinder->bottom, center, tmp);
	vector_add(&cylinder->top, center, tmp);
	obj = object_new(OBJ_CYLINDER, cylinder, color);
	if (scene->object_count > 0)
		obj->next = scene->objects;
	scene->objects = obj;
	return (scene->object_count++, 1);
}
