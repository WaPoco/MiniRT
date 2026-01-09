/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:55:38 by vpogorel          #+#    #+#             */
/*   Updated: 2026/01/09 13:53:03 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

int	intersect_cylinder(t_cylinder *cylinder, t_ray ray,
				t_hit *out)
{
	t_tuple	m;
	double	ray_a[2];

	vector_diff(&m, ray.origin, cylinder->bottom);
	//printf("\n\naxis=(x,y,z)=(%f,%f,%f)\n\n", cylinder->axis.x, cylinder->axis.y, cylinder->axis.z);
	ray_a[0] = scalar_product(cylinder->axis, ray.direction);
	//printf("ray_a[0]=%f\n", ray_a[0]);
	ray_a[1] = scalar_product(cylinder->axis, m);
	//printf("ray_a[1]=%f\n", ray_a[1]);
	out->obj->mat.color = cylinder->color;
	out->t[0] = 1e30;
	cap_down(ray, out, ray_a);
	cap_up(ray, out, ray_a);
	lateral_surface(ray, out, ray_a, m);
	if (out->t[0] < 1e30)
	{
		//t_tuple  cross= cross_product(out->point, cylinder->axis);
		//printf("cross=%f\n", sqrt(sq_euclidean_distance(cross, create_tuple(0,0,0))));
		//printf("normale %f, %f ,%f\n", out->normal.x, out->normal.y, out->normal.z);
		//printf("point %f, %f ,%f\n", out->point.x, out->point.y, out->point.z);
		return (1);
	}
	return (0);
}

int	intersect_plane(t_plane *plane, t_ray ray, t_hit *out)
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
			out->normal = plane->normal;
			out->obj->mat.color = plane->color;
			return (1);
		}
	}
	return (0);
}

int	intersect_sphere(t_sphere *sphere, t_ray ray, t_hit *out)
{
	double	result[2];
	double	sq_euclid_dis_ray;
	double	discriminant;
	t_tuple	dis_origins;
	t_tuple	neg_c_sphere;
	double	t;

	sq_euclid_dis_ray = sq_euclidean_distance(ray.direction, create_tuple(0, 0, 0));
	vector_neg(&neg_c_sphere, sphere->center);
	vector_add(&dis_origins, ray.origin, neg_c_sphere);
	result[1] = scalar_product(ray.direction, dis_origins);
	result[0] = -4.0 * sq_euclid_dis_ray * (sq_euclidean_distance(dis_origins, create_tuple(0, 0, 0)) - sphere->radius * sphere->radius);
	discriminant = 2.0 * result[1] * 2.0 * result[1] + result[0];
	if (discriminant < 0)
		return (0);
	else if (discriminant >= 0)
	{
		t = (-2.0 * result[1] + sqrt(discriminant))
			/ (2.0 * sq_euclid_dis_ray);
		//printf("t0=%f\n", t);
		if (t > 1e-6)
			out->t[0] = t;
		t = (-2.0 * result[1] - sqrt(discriminant))
			/ (2.0 * sq_euclid_dis_ray);
		//printf("t1=%f\n", t);
		if (t > 1e-6)
			out->t[1] = t;
		swap_min(&out->t[0], &out->t[1]);
		get_points(&out->point, ray.direction, ray.origin, out->t);
		vector_diff(&out->normal, out->point, sphere->center);
		vector_norm(&out->normal, out->normal);
		out->obj->mat.color = sphere->color;
	}
	return (1);
}

int	intersect_object(t_object *obj, t_ray ray, t_hit *out)
{
	if (!obj)
		return (0);
	out->obj = obj;
	if (obj->type == OBJ_SPHERE)
		return (intersect_sphere((t_sphere *)obj->shape, ray, out));
	if (obj->type == OBJ_PLANE)
		return (intersect_plane((t_plane *)obj->shape, ray, out));
	if (obj->type == OBJ_CYLINDER)
		return (intersect_cylinder((t_cylinder *)obj->shape, ray, out));
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
			//printf("t[1]=%f t[0]=%f point (x =%f, y=%f, z=%f) \n", tmp.t[1], tmp.t[0], tmp.point.x, tmp.point.y, tmp.point.z);
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
