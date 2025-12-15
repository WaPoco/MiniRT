/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:30:17 by vpogorel          #+#    #+#             */
/*   Updated: 2025/12/10 21:54:55 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

typedef struct a_camera
{
	double	vsize;
	double	hsize;
	double	field_of_view;
	double	pixel_size;
	double	half_width;
	double	half_height;
	double	aspect;
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
	t_tuple		c;
}	t_data;

int			create_trgb(int t, int r, int g, int b);
int			close_window(t_data *data);
//void		click_button(int x, int y, int button, t_data *data);
//int			mouse_click(int button, int x, int y, t_data *data);
//int			key_press(int key, t_data *data);
int			create_trgb(int t, int r, int g, int b);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		create_img(t_data *data, t_ray ray, int x, int y);
double		scalar_product(t_tuple a, t_tuple b);
t_tuple		*int_section_sphere(t_tuple ray, t_tuple o_ray, t_tuple c_sphere, double r_sphere);
t_tuple		*int_section_plane(t_ray ray, t_plane plane);
double		sq_euclidean_distance(t_tuple a, t_tuple b);
double		euclidean_distance(t_tuple a, t_tuple b);
void		vector_add(t_tuple *result, t_tuple a, t_tuple b);
void		vector_neg(t_tuple *result, t_tuple a);
void		vector_diff(t_tuple *result, t_tuple a, t_tuple b);
void		vector_reflexion(t_tuple *result, t_tuple ray, t_tuple normal);
void		vector_scale(t_tuple *result, t_tuple a, double factor);
void		vector_norm(t_tuple *result, t_tuple a);
void		get_points(t_tuple *P, t_tuple ray, t_tuple o_ray, double d[]);
double		lighting(t_tuple ray, t_tuple p_light, t_tuple point, t_tuple p_eye, t_tuple normalv);
void		ajust_camera(t_camera *camera);
t_ray		ray_for_pixel(t_camera camera, int px, int py);
t_tuple		create_tuple(double x, double y, double z);
t_tuple		matrix_mult(double **matrix, t_tuple point);
double		**transpose(double **matrix, int size);
double		**inverse_matrix(double **matrix);
double		**extract_adj(int i, int j, double **matrix);
double		det_adj(int i, int j, double **matrix);
double		det_4x4(double **matrix);
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
void		scaling(t_tuple *P, double x, double y, double z);
//int			iteration(t_complex z_0, t_complex c, t_data *data);

#endif
