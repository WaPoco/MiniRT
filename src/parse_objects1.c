/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 13:27:07 by vpogorel          #+#    #+#             */
/*   Updated: 2026/01/06 09:52:48 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

int	parse_ambient(char **t, t_world *scene)
{
	double	ratio;
	t_color	color;

	if (scene->ambient.is_set)
		return (0);
	if (!t[1] || !t[2] || t[3])
		return (0);
	if (!parse_double(t[1], &ratio))
		return (0);
	if (ratio < 0.0 || ratio > 1.0)
		return (0);
	if (!parse_color(t[2], &color))
		return (0);
	scene->ambient.ratio = ratio;
	scene->ambient.color = color;
	scene->ambient.is_set = 1;
	return (1);
}

int	parse_camera(char **t, t_world *scene)
{
	t_camera	camera;
	t_tuple		position;
	t_tuple		orientation;
	double		horizontal_view;

	if (scene->camera.is_set)
		return (0);
	if (!t[1] || !t[2] || !t[3] || t[4])
		return (0);
	if (!parse_tuple(t[1], &position) || !parse_tuple(t[2], &orientation))
		return (0);
	if (orientation.x < -1.0 || orientation.x > 1.0
		|| orientation.y < -1.0 || orientation.y > 1.0
		|| orientation.z < -1.0 || orientation.z > 1.0)
		return (0);
	if (!parse_double(t[3], &horizontal_view))
		return (0);
	if (horizontal_view < 0.0 || horizontal_view > 180.0)
		return (0);
	camera.from = position;
	camera.to = orientation;
	camera.up = create_tuple(0, 1, 0);
	camera.field_of_view = horizontal_view * acos(-1) / 180.0 ;
	scene->camera = camera;
	scene->camera.is_set = 1;
	return (1);
}

int	parse_light(char **t, t_world *scene)
{
	t_light	light;
	t_tuple	position;
	double	intensity;
	t_color	color;

	if (scene->light.is_set)
		return (0);
	if (!t[1] || !t[2] || !t[3] || t[4])
		return (0);
	if (!parse_tuple(t[1], &position))
		return (0);
	if (!parse_double(t[2], &intensity))
		return (0);
	if (intensity < 0.0 || intensity > 1.0)
		return (0);
	if (!parse_color(t[3], &color))
		return (0);
	light.position = position;
	light.intensity = intensity;
	light.color = color;
	scene->light = light;
	scene->light.is_set = 1;
	return (1);
}

int	parse_sphere(char **t, t_world *scene)
{
	t_sphere	*sphere;
	t_object	*obj;
	t_tuple		center;
	double		diameter;
	t_color		color;

	if (!t[1] || !t[2] || !t[3] || t[4])
		return (0);
	if (!parse_tuple(t[1], &center) || !parse_double(t[2], &diameter))
		return (0);
	if (diameter <= 0.0)
		return (0);
	if (!parse_color(t[3], &color))
		return (0);
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (0);
	sphere->center = center;
	sphere->radius = diameter / 2.0;
	sphere->color = color;
	obj = object_new(OBJ_SPHERE, sphere, color);
	obj->mat.diffuse = 0.9;
	obj->mat.specular = 0.9;
	obj->mat.shininess = 2000;
	if (scene->object_count > 0)
		obj->next = scene->objects;
	scene->objects = obj;
	return (scene->object_count++, 1);
}

int	parse_plane(char **t, t_world *scene)
{
	t_plane		*plane;
	t_object	*obj;
	t_tuple		point;
	t_tuple		normal;
	t_color		color;

	if (!t[1] || !t[2] || !t[3] || t[4])
		return (0);
	if (!parse_tuple(t[1], &point) || !parse_tuple(t[2], &normal)
		|| !parse_color(t[3], &color))
		return (0);
	if (normal.x < -1.0 || normal.x > 1.0
		|| normal.y < -1.0 || normal.y > 1.0
		|| normal.z < -1.0 || normal.z > 1.0)
		return (0);
	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (0);
	plane->point = point;
	plane->normal = normal;
	plane->color = color;
	obj = object_new(OBJ_PLANE, plane, color);
	if (scene->object_count > 0)
		obj->next = scene->objects;
	scene->objects = obj;
	return (scene->object_count++, 1);
}
