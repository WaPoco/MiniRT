/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:55:38 by vpogorel          #+#    #+#             */
/*   Updated: 2025/12/27 23:06:28 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

int	intersect_plane(t_plane *plane, t_ray ray, t_hit *out, t_object *obj)
{
	t_tuple	p_to_o;
	double	denom;
	double	t;

	denom = scalar_product(plane->normal, ray.direction);
	if (fabs(denom) > 1e-6)
	{
		vector_diff(&p_to_o, plane->point, ray.origin);
		t = scalar_product(p_to_o, plane->normal) / denom;
		if (t > 0)
		{
			out->t[0] = t;
			get_points(&out->point, ray.direction, ray.origin, out->t);
			return (1);
		}
	}
	return (0);
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

int	intersect_sphere(t_sphere *sphere, t_ray ray, t_hit *out, t_object *obj)
{
	double	result[2];
	double	sq_euclid_dis_ray;
	double	discriminant;
	t_tuple	dis_origins;
	t_tuple	neg_c_sphere;

	sq_euclid_dis_ray = sq_euclidean_distance(ray.direction, create_tuple(0, 0, 0));
	vector_neg(&neg_c_sphere, sphere->center);
	vector_add(&dis_origins, ray.origin, neg_c_sphere);
	result[1] = scalar_product(ray.direction, dis_origins);
	result[0] = -4 * sq_euclid_dis_ray * (sq_euclidean_distance(dis_origins, create_tuple(0, 0, 0)) - sphere->radius * sphere->radius);
	discriminant = 2 * result[1] * 2 * result[1] + result[0];
	if (discriminant < 0)
		return (0);
	else if (discriminant >= 0)
	{
		out->t[0] = (-2 * result[1] + sqrt(discriminant))
			/ (2 * sq_euclid_dis_ray);
		out->t[1] = (-2 * result[1] - sqrt(discriminant))
			/ (2 * sq_euclid_dis_ray);
		swap_min(&out->t[0], &out->t[1]);
	}
	return (get_points(&out->point, ray.direction, ray.origin, out->t), 1);
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

int	intersect_object(t_object *obj, t_ray ray, t_hit *out)
{
	if (!obj)
		return (0);
	if (obj->type == OBJ_SPHERE)
		return (intersect_sphere((t_sphere *)obj->shape, ray, out, obj));
	if (obj->type == OBJ_PLANE)
		return (intersect_plane((t_plane *)obj->shape, ray, out, obj));
	if (obj->type == OBJ_CYLINDER)
		return (intersect_cylinder((t_cylinder *)obj->shape, ray, out, obj));
	return (0);
}

int	intersect_world(t_world *w, t_ray ray, t_hit *out)
{
	t_object	*cur;
	t_hit		tmp;
	int			hit_any;
	double		closest;

	hit_any = 0;
	closest = 1e30;
	cur = w->objects;
	while (cur)
	{
		if (intersect_object(cur, ray, &tmp))
		{
			if (tmp.t[0] > 1e-6 && tmp.t[0] < closest)
			{
				closest = tmp.t[0];
				*out = tmp;
				hit_any = 1;
			}
		}
		cur = cur->next;
	}
	return (hit_any);
}
