/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:55:38 by vpogorel          #+#    #+#             */
/*   Updated: 2025/12/18 21:27:32 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

t_tuple	*int_section_plane(t_ray ray, t_plane plane)
{
	double	d[2];
	t_tuple	*p;
	t_tuple	p_to_o;
	double	denom;
	double	t;

	p[0].x = 0;
	p[0].y = 0;
	p[0].z = 0;
	p = malloc(sizeof(t_tuple) * 2);
	if (!p)
		return (NULL);
	d[0] = 0;
	denom = scalar_product(plane.normal, ray.direction);
	if (fabs(denom) > 1e-6)
	{
		vector_diff(&p_to_o, plane.point, ray.origin);
		t = scalar_product(p_to_o, plane.normal) / denom;
		if (t > 0)
		{
			d[0] = t;
			get_points(p, ray.direction, ray.origin, d);
		}
	}
	return (d[1] = 0, p);
}

static void	swap_min(double *a, double *b)
{
	double	tmp;

	if (*a > *b)
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
}

t_tuple	*int_section_sphere(t_ray ray, t_sphere sphere)
{
	double	result[2];
	double	sq_euclid_dis_ray;
	double	discriminant;
	double	d[2];
	t_tuple	dis_origins;
	t_tuple	neg_c_sphere;
	t_tuple	*p;

	sq_euclid_dis_ray = sq_euclidean_distance(ray.direction, create_tuple(0, 0, 0));
	p = calloc(sizeof(t_tuple), 2);
	vector_neg(&neg_c_sphere, sphere.center);
	vector_add(&dis_origins, ray.origin, neg_c_sphere);
	result[1] = scalar_product(ray.direction, dis_origins);
	result[0] = -4 * sq_euclid_dis_ray * (sq_euclidean_distance(dis_origins, create_tuple(0, 0, 0)) - sphere.radius * sphere.radius);
	discriminant = 2 * result[1] * 2 * result[1] + result[0];
	if (discriminant < 0)
		return (p);
	else if (discriminant >= 0)
	{
		d[0] = (-2 * result[1] + sqrt(discriminant))
			/ (2 * sq_euclid_dis_ray);
		d[1] = (-2 * result[1] - sqrt(discriminant))
			/ (2 * sq_euclid_dis_ray);
		swap_min(&d[0], &d[1]);
	}
	return (get_points(p, ray.direction, ray.origin, d), p);
}

void	get_points(t_tuple *P, t_tuple ray, t_tuple o_ray, double d[])
{
	t_tuple	scale_vec;
	t_tuple	result;
	int		i;

	i = 0;
	while (i < 2)
	{
		vector_scale(&scale_vec, ray, d[i]);
		vector_add(&result, o_ray, scale_vec);
		P[i].x = result.x;
		P[i].y = result.y;
		P[i].z = result.z;
		i++;
	}
}
