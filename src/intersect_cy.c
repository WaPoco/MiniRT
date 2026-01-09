/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:42:26 by vpogorel          #+#    #+#             */
/*   Updated: 2026/01/09 13:31:01 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

int	discriminant(t_tuple d_perp, t_tuple m_perp, double *ray_a, t_hit *out)
{
	double	tmp[3];
	double	delta;
	double	t;
	int		hit;
	double	radius;
	double	height;

	hit = 0;
	radius = ((t_cylinder *)out->obj->shape)->radius;
	height = ((t_cylinder *)out->obj->shape)->height;
	tmp[0] = scalar_product(d_perp, d_perp);
	//printf("scal(d_per, d_perp) %f\n", tmp[0]);	
	tmp[1] = 2.0 * scalar_product(m_perp, d_perp);
	//printf("scal(m_per, d_perp) %f\n", tmp[1]);	
	tmp[2] = scalar_product(m_perp, m_perp) - radius * radius;
	//printf("scal(m_per, m_perp) - radius * radius %f\n", tmp[2]);	
	delta = tmp[1] * tmp[1] - 4.0 * tmp[0] * tmp[2];
	//printf("delta %f\n", delta);
	if (delta >= 0)
	{
		t = (-tmp[1] + sqrt(delta)) / (2.0 * tmp[0]);
		if (t > 1e-6 && 0 <= ray_a[1] + t * ray_a[0] && ray_a[1] + t * ray_a[0] <= height)
		{
			if (t < out->t[0])
				out->t[0] = t;
			hit = 1;
		}
		t = (-tmp[1] - sqrt(delta)) / (2.0 * tmp[0]);
		if (t > 1e-6 && 0 <= ray_a[1] + t * ray_a[0] && ray_a[1] + t * ray_a[0] <= height)
		{
			if (t < out->t[0])
				out->t[0] = t;
			hit = 1;
		}
		//printf("point %f\n", out->t[0]);
		return (hit);
	}
	return (0);
}

t_tuple	perp_comp(t_tuple vec, double d, t_tuple axis)
{
	t_tuple	vec_paral;
	t_tuple	vec_perp;

	//printf("vec=(x,y,z)=(%f,%f,%f)\n", vec.x, vec.y, vec.z);
	//printf("axis=(x,y,z)=(%f,%f,%f)\n", axis.x, axis.y, axis.z);
	//printf("d=%f\n", d);
	vector_scale(&vec_paral, axis, d);
	//printf("vec_paral=(x,y,z)=(%f,%f,%f)\n", vec_paral.x, vec_paral.y, vec_paral.z);
	vector_diff(&vec_perp, vec, vec_paral);
	return (vec_perp);
}

int	lateral_surface(t_ray ray, t_hit *out,
			double *ray_a, t_tuple m)
{
	t_tuple		m_perp;
	t_tuple		d_perp;
	t_cylinder	*cy;
	int			hit;

	hit = 0;
	cy = (t_cylinder *)out->obj->shape;
	//printf("axis (x,y,z)=(%f,%f,%f)\n", cy->axis.x, cy->axis.y, cy->axis.z);
	d_perp = perp_comp(ray.direction, ray_a[0], cy->axis);
	m_perp = perp_comp(m, ray_a[1], cy->axis);
	//printf("d_perp (x,y,z)=(%f,%f,%f)\n", d_perp.x, d_perp.y, d_perp.z);
	//printf("m_perp (x,y,z)=(%f,%f,%f)\n", m_perp.x, m_perp.y, m_perp.z);
	if (fabs(scalar_product(d_perp, d_perp)) < 1e-6)
		return (0);
	hit = discriminant(d_perp, m_perp, ray_a, out);
	if (out->t[0] < 1e30)
	{
		get_points(&out->point, ray.direction, ray.origin, out->t);
		vector_diff(&out->normal, out->point, cy->center);
		out->normal = perp_comp(out->normal,
				scalar_product(out->normal, cy->axis), cy->axis);
		vector_norm(&out->normal, out->normal);
	}
	return (hit);
}

int	cap_up(t_ray ray, t_hit *out,
			double *ray_a)
{
	double		t;
	t_tuple		v_b;
	t_tuple		p_b;
	t_cylinder	*cy;

	cy = (t_cylinder *)out->obj->shape;
	if (fabs(ray_a[0]) > 1e-6)
	{
		t = (cy->height - ray_a[1]) / ray_a[0];
		if (t > 1e-6)
		{
			get_points(&p_b, ray.direction, ray.origin, &t);
			vector_diff(&v_b, p_b, cy->top);
			if (sq_euclidean_distance(v_b, create_tuple(0, 0, 0))
				<= cy->radius * cy->radius)
			{
				if (t < out->t[0])
				{
					out->t[0] = t;
					vector_norm(&out->normal, cy->axis);
				}
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

	cy = (t_cylinder *)out->obj->shape;
	if (fabs(ray_a[0]) > 1e-6)
	{
		t = -(ray_a[1]) / ray_a[0];
		//printf("t=%f\n", t);
		if (t > 1e-6)
		{
			get_points(&p_b, ray.direction, ray.origin, &t);
			vector_diff(&v_b, p_b, cy->bottom);
			//printf("v_b=(x,y,z)=(%f,%f,%f)\n", v_b.x, v_b.y, v_b.z);
			if (sq_euclidean_distance(v_b, create_tuple(0, 0, 0))
				<= cy->radius * cy->radius)
			{
				//printf("Down\n");
				if (t < out->t[0])
				{
					out->t[0] = t;
					vector_neg(&out->normal, cy->axis);
					vector_norm(&out->normal, out->normal);
				}
				return (1);
			}
		}
	}
	return (0);
}
