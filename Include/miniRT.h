/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:30:17 by vpogorel          #+#    #+#             */
/*   Updated: 2025/12/26 00:15:24 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

typedef struct s_hit
{
	double		t[2];
	t_tuple		point;
	t_tuple		normal;
	t_object	*obj;
}	t_hit;

typedef enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}	t_obj_type;

typedef struct s_material
{
	t_color	color;
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
}	t_material;

typedef struct s_object
{
	t_obj_type			type;
	t_material			mat;
	void				*shape;
	struct s_object		*next;
}	t_object;

typedef struct s_light
{
	t_tuple	position;
	double	intensity;
	t_color	color;
}	t_light;

typedef struct s_world
{
	t_camera	camera;
	t_light		light;
	t_object	*objects;
	double		ambient_ratio;
	t_color		ambient_color;
}	t_world;

typedef struct a_camera
{
	double	vsize;
	double	hsize;
	double	field_of_view;
	double	pixel_size;
	double	half_width;
	double	half_height;
	double	aspect;
	t_tuple	position;
	t_tuple	from;
	t_tuple	to;
	t_tuple	up;
	double	**transform;
}	t_camera;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_tuple
{
	double	x;
	double	y;
	double	z;
	int		type;	
}	t_tuple;

typedef struct sphere
{
	t_tuple	center;
	t_color	color;
	double	radius;
	double	**transfrom;
}	t_sphere;

typedef struct plane
{
	t_tuple	point;
	t_tuple	normal;
	t_color	color;
	double	**transfrom;
}	t_plane;

typedef struct s_cylinder
{
	t_tuple	center;
	t_tuple	axis;
	double	radius;
	double	height;
	double	**transform;
}	t_cylinder;

typedef struct s_ray
{
	t_tuple	origin;
	t_tuple	direction;
}	t_ray;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			win_width;
	int			win_height;
	t_world		*world;
}	t_data;

int			create_trgb(int t, int r, int g, int b);
int			close_window(t_data *data);
//int			mouse_click(int button, int x, int y, t_data *data);
//int			key_press(int key, t_data *data);
int			create_trgb(int t, int r, int g, int b);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		create_img(t_data *data, t_ray ray, int x, int y);
double		scalar_product(t_tuple a, t_tuple b);
int			intersect_sphere(t_sphere *sphere, t_ray ray, t_hit *out, t_object *obj);
int			intersect_plane(t_plane *plane, t_ray ray, t_hit *out, t_object *obj);
double		sq_euclidean_distance(t_tuple a, t_tuple b);
double		euclidean_distance(t_tuple a, t_tuple b);
void		vector_add(t_tuple *result, t_tuple a, t_tuple b);
void		vector_neg(t_tuple *result, t_tuple a);
void		vector_diff(t_tuple *result, t_tuple a, t_tuple b);
void		vector_reflexion(t_tuple *result, t_tuple ray, t_tuple normal);
void		vector_scale(t_tuple *result, t_tuple a, double factor);
void		vector_norm(t_tuple *result, t_tuple a);
void		get_points(t_tuple *P, t_tuple ray, t_tuple o_ray, double d[]);
t_color		lighting(t_world *world, t_ray *ray, t_hit *hit, t_tuple p_eye);
void		ajust_camera(t_data *data);
t_ray		ray_for_pixel(t_camera camera, int px, int py);
t_tuple		create_tuple(double x, double y, double z);
t_tuple		matrix_mult(double **matrix, t_tuple point);
double		**transpose(double **matrix, int size);
double		**inverse_matrix(double **matrix);
double		**extract_adj(int i, int j, double **matrix);
double		det_adj(int i, int j, double **matrix);
double		det_nxn(double **matrix, int n);
double		**scalar_product_matrix(double **matrix, double scalar);
t_tuple		cross_product(t_tuple a, t_tuple b);
t_color		create_color(double r, double g, double b);
t_color		color_add(t_color a, t_color b);
t_color		color_scale(t_color c, double factor);
int			color_to_trgb(t_color c);
double		clamp(double x);
double		**allocate_4x4_matrix();
double		**translation_matrix(double x, double y, double z);
double		**matrix_mult_4x4(double **a, double **b);
double		**view_transform(t_tuple from, t_tuple to, t_tuple up);
void		free_4x4_matrix(double **matrix);
int			extract_adj_assign(int *n, double **matrix, double **adj);
void		scaling(t_tuple *P, double x, double y, double z);
int			intersect_world(t_world *w, t_ray ray, t_hit *out);

#endif
