/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:55:38 by vpogorel          #+#    #+#             */
/*   Updated: 2026/01/01 22:35:53 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/miniRT.h"

int	discriminant(t_tuple d_perp, t_tuple m_perp, double radius, t_hit *out)
{
	double	a;
	double	b;
	double	c;
	double	delta;

	a = scalar_product(d_perp, d_perp);
	b = 2 * scalar_product(m_perp, d_perp);
	c = scalar_product(m_perp, m_perp) - radius * radius;
	delta = b * b - 4 * a * c;
	if (delta >= 0)
	{
		out->t[0] = -b + sqrt(delta) / (2 * a);
		out->t[1] = -b - sqrt(delta) / (2 * a);
	}
	if (out->t[0] > 1e-6)
	return (delta);
}

t_tuple	perp_comp(t_tuple vec, double d, t_tuple axis)
{
	t_tuple	vec_paral;
	t_tuple	vec_perp;

	vector_scale(&vec_paral, axis, d);
	vector_diff(&vec_perp, vec, vec_paral);
	return (vec_perp);
}

int	leteral_surface(t_cylinder *cylinder, t_ray ray,
				t_hit *out)
{
	t_tuple	m;
	t_tuple	b;
	t_tuple	m_perp;
	t_tuple	d_perp;
	double	ray_a[2];

	vector_scale(&b, cylinder->axis, -cylinder->height / 2);
	vector_diff(&m, ray.origin, b);
	ray_a[0] = scalar_product(cylinder->axis, ray.direction);
	ray_a[1] = scalar_product(cylinder->axis, m);
	d_perp = perp_comp(ray.direction, ray_a[0], cylinder->axis);
	m_perp = perp_comp(m, ray_a[1], cylinder->axis);
	if (fabs(scalar_product(d_perp, d_perp)) < 1e-6)
		return (0);
	return (discriminant(d_perp, m_perp, cylinder->radius, out));
}

int	intersect_cylinder(t_cylinder *cylinder, t_ray ray,
				t_hit *out)
{
	cap_up();
	cap_down();
	leteral_surface(cylinder, ray, out);
	return (1);
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
			return (1);
		}
	}
	return (0);
}

void	swap_min(double *a, double *b)
{
	double	tmp;

	if (*a > *b)
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
}

int	intersect_sphere(t_sphere *sphere, t_ray ray, t_hit *out)
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

static void	cyl_ctx_init(t_cy_ctx *ctx, t_cylinder *cy, t_ray ray)
{
	vector_norm(&ctx->axis, cy->axis);
	vector_diff(&ctx->oc, ray.origin, cy->center);
	ctx->center = cy->center;
	ctx->dot_d_a = scalar_product(ray.direction, ctx->axis);
	ctx->dot_oc_a = scalar_product(ctx->oc, ctx->axis);
	ctx->half_h = cy->height * 0.5;
	ctx->radius = cy->radius;
}

static int	cyl_add(double *t, int count, double value)
{
	if (value > 1e-6 && count < 4)
		t[count++] = value;
	return (count);
}

static int	cyl_in_height(t_cy_ctx *ctx, double t)
{
	double	h;

	h = ctx->dot_oc_a + t * ctx->dot_d_a;
	if (fabs(h) <= ctx->half_h + 1e-6)
		return (1);
	return (0);
}

static int	cyl_side_hits(t_cy_ctx *ctx, t_ray ray, double *t)
{
	t_cy_calc	c;
	int			count;
	vector_scale(&c.tmp, ctx->axis, ctx->dot_d_a);
	vector_diff(&c.d_perp, ray.direction, c.tmp);
	vector_scale(&c.tmp, ctx->axis, ctx->dot_oc_a);
	vector_diff(&c.oc_perp, ctx->oc, c.tmp);
	c.a = scalar_product(c.d_perp, c.d_perp);
	c.b = 2.0 * scalar_product(c.d_perp, c.oc_perp);
	c.c = scalar_product(c.oc_perp, c.oc_perp) - ctx->radius * ctx->radius;
	count = 0;
	if (fabs(c.a) < 1e-12)
		return (0);
	c.disc = c.b * c.b - 4.0 * c.a * c.c;
	if (c.disc < 0.0)
		return (0);
	c.t = (-c.b - sqrt(c.disc)) / (2.0 * c.a);
	if (cyl_in_height(ctx, c.t))
		count = cyl_add(t, count, c.t);
	c.t = (-c.b + sqrt(c.disc)) / (2.0 * c.a);
	if (cyl_in_height(ctx, c.t))
		count = cyl_add(t, count, c.t);
	return (count);
}

static double	cyl_cap_t(t_cy_ctx *ctx, t_ray ray, t_tuple cap)
{
	t_tuple	p;
	t_tuple	v;
	t_tuple	tmp;
	double	denom;
	double	t;

	denom = scalar_product(ray.direction, ctx->axis);
	if (fabs(denom) < 1e-6)
		return (0.0);
	vector_diff(&tmp, cap, ray.origin);
	t = scalar_product(tmp, ctx->axis) / denom;
	if (t <= 1e-6)
		return (0.0);
	vector_scale(&p, ray.direction, t);
	vector_add(&p, ray.origin, p);
	vector_diff(&v, p, cap);
	if (scalar_product(v, v) > ctx->radius * ctx->radius + 1e-6)
		return (0.0);
	return (t);
}

static int	cyl_cap_hits(t_cy_ctx *ctx, t_ray ray, double *t, int count)
{
	t_tuple	cap;
	t_tuple	tmp;
	double	tcap;

	vector_scale(&tmp, ctx->axis, ctx->half_h);
	vector_add(&cap, ctx->center, tmp);
	tcap = cyl_cap_t(ctx, ray, cap);
	count = cyl_add(t, count, tcap);
	vector_scale(&tmp, ctx->axis, -ctx->half_h);
	vector_add(&cap, ctx->center, tmp);
	tcap = cyl_cap_t(ctx, ray, cap);
	return (cyl_add(t, count, tcap));
}

static void	cyl_pick_two(double *t, int count, double out[2])
{
	int		i;
	double	a;
	double	b;

	a = 1e30;
	b = 1e30;
	i = 0;
	while (i < count)
	{
		if (t[i] < a)
		{
			b = a;
			a = t[i];
		}
		else if (t[i] < b)
			b = t[i];
		i++;
	}
	if (count == 1)
		b = a;
	out[0] = a;
	out[1] = b;
}

int	intersect_cylinder(t_cylinder *cylinder, t_ray ray, t_hit *out)
{
	t_cy_ctx	ctx;
	double		t[4];
	int			count;

	cyl_ctx_init(&ctx, cylinder, ray);
	count = cyl_side_hits(&ctx, ray, t);
	count = cyl_cap_hits(&ctx, ray, t, count);
	if (count == 0)
		return (0);
	cyl_pick_two(t, count, out->t);
	return (get_points(&out->point, ray.direction, ray.origin, out->t), 1);
}

int	intersect_object(t_object *obj, t_ray ray, t_hit *out)
{
	if (!obj)
		return (0);
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
