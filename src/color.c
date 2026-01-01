/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:55:09 by vpogorel          #+#    #+#             */
/*   Updated: 2025/12/30 18:19:52 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

t_color	create_color(double r, double g, double b)
{
	return ((t_color){r, g, b});
}

t_color	color_scale(t_color c, double s)
{
	return ((t_color){c.r * s, c.g * s, c.b * s});
}

t_color	color_add(t_color a, t_color b)
{
	return ((t_color){a.r + b.r, a.g + b.g, a.b + b.b});
}

double	clamp(double x)
{
	if (x < 0)
		return (0);
	if (x > 1)
		return (1);
	return (x);
}

int	color_to_trgb(t_color c)
{
	int	r;
	int	g;
	int	b;

	r = (int)(clamp(c.r) * 255);
	g = (int)(clamp(c.g) * 255);
	b = (int)(clamp(c.b) * 255);
	return (create_trgb(0, r, g, b));
}

t_color	lighting(t_world *world, t_ray *ray, t_hit *hit, t_tuple p_eye)
{
	(void)ray;
	double	scalar[2] = {0, 0};
	double	factor;
	t_color	ambient;
	t_color	diffuse;
	t_color specular;
	t_tuple	L;
	t_tuple	normal;
	t_tuple	R;
	t_tuple	V;

	vector_diff(&L, world->light.position, hit->point);
	vector_norm(&L, L);
	vector_norm(&normal, hit->normal);
	ambient = color_scale(hit->obj->mat.color, world->ambient.ratio * world->light.intensity);
	diffuse = create_color(0, 0, 0);
	scalar[0] = scalar_product(L, normal);
	if (scalar[0] > 0)
		diffuse = color_scale(hit->obj->mat.color, hit->obj->mat.diffuse * world->light.intensity * scalar[1]);
	vector_diff(&V, p_eye, hit->point);
	vector_norm(&V, V);
	specular = create_color(0, 0, 0);
	if (scalar[0] > 0)
	{
		vector_scale(&L, L, -1);
		vector_reflexion(&R, L, normal);
		vector_norm(&R, R);
		scalar[1] = scalar_product(R, V);
		if (scalar[1] > 0)
		{
			factor = pow(scalar[1], hit->obj->mat.shininess);
			specular = color_scale(create_color(1, 1, 1), hit->obj->mat.specular * world->light.intensity * factor);
		}
	}
	return (color_add(ambient, color_add(diffuse, specular)));
}
