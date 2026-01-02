/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:42:26 by vpogorel          #+#    #+#             */
/*   Updated: 2026/01/02 16:15:04 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

int	discriminant(t_tuple d_perp, t_tuple m_perp, double *ray_a, t_hit *out)
{
	double	tmp[3];
	double	delta;
	double	t;
	double	radius;
	double	height;

	radius = ((t_cylinder *)out->obj->shape)->radius;
	height = ((t_cylinder *)out->obj->shape)->height;
	tmp[0] = scalar_product(d_perp, d_perp);
	tmp[1] = 2.0 * scalar_product(m_perp, d_perp);
	tmp[2] = scalar_product(m_perp, m_perp) - radius * radius;
	delta = tmp[1] * tmp[1] - 4.0 * tmp[0] * tmp[2];
	if (delta >= 0)
	{
		t = -tmp[1] + sqrt(delta) / (2.0 * tmp[0]);
		if (t > 1e-6 && fabs(ray_a[0] + t * ray_a[1]) <= height)
			out->t[0] = t;
		t = -tmp[1] - sqrt(delta) / (2.0 * tmp[0]);
		if (t > 1e-6 && fabs(ray_a[0] + t * ray_a[1]) <= height)
			out->t[1] = t;
	}
	swap_min(&out->t[0], &out->t[1]);
	return (1);
}

t_tuple	perp_comp(t_tuple vec, double d, t_tuple axis)
{
	t_tuple	vec_paral;
	t_tuple	vec_perp;

	vector_scale(&vec_paral, axis, d);
	vector_diff(&vec_perp, vec, vec_paral);
	return (vec_perp);
}

int	leteral_surface(t_ray ray, t_hit *out,
			double *ray_a, t_tuple m)
{
	t_tuple		m_perp;
	t_tuple		d_perp;
	t_cylinder	*cy;

	cy = (t_cylinder *)out->obj;
	d_perp = perp_comp(ray.direction, ray_a[0], cy->axis);
	m_perp = perp_comp(m, ray_a[1], cy->axis);
	if (fabs(scalar_product(d_perp, d_perp)) < 1e-6)
		return (0);
	discriminant(d_perp, m_perp, &ray_a[0], out);
	get_points(&out->point, ray.direction, ray.origin, out->t);
	return (1);
}

int	cap_up(t_ray ray, t_hit *out,
			double *ray_a)
{
	double		t;
	t_tuple		v_b;
	t_tuple		p_b;
	t_cylinder	*cy;

	cy = (t_cylinder *)out->obj;
	if (fabs(ray_a[0]) > 1e-6)
	{
		t = (cy->height - ray_a[1]) / ray_a[0];
		if (t > 1e-6)
		{
			get_points(&p_b, ray.direction, ray.origin, out->t);
			vector_diff(&v_b, p_b, cy->top);
			if (sq_euclidean_distance(v_b, create_tuple(0, 0, 0))
				<= cy->radius * cy->radius)
			{
				get_points(&out->point, ray.direction, ray.origin, out->t);
				return (1);
			}
		}
	}
	return (0);
}

int	cap_down(t_ray ray, t_hit *out,
			double *ray_a)
{
	double		t;
	t_tuple		v_b;
	t_tuple		p_b;
	t_cylinder	*cy;

	cy = (t_cylinder *)out->obj;
	t = 0;
	if (fabs(ray_a[0]) > 1e-6)
	{
		t = -ray_a[1] / ray_a[0];
		if (t > 1e-6)
		{
			get_points(&p_b, ray.direction, ray.origin, out->t);
			vector_diff(&v_b, p_b, cy->bottom);
			if (sq_euclidean_distance(v_b, create_tuple(0, 0, 0))
				<= cy->radius * cy->radius)
			{
				get_points(&out->point, ray.direction, ray.origin, out->t);
				return (1);
			}
		}
	}
	return (0);
}
