/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:30:17 by vpogorel          #+#    #+#             */
/*   Updated: 2025/12/31 16:28:05 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>

typedef enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}	t_obj_type;

typedef struct s_tuple
{
	double	x;
	double	y;
	double	z;
	int		type;	
}	t_tuple;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_material
{
	t_color	color;
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

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
	int		is_set;
}	t_ambient;

typedef struct s_light
{
	t_tuple	position;
	double	intensity;
	int		is_set;
	t_color	color;
}	t_light;

typedef struct a_camera
{
	double	vsize;
	double	hsize;
	double	field_of_view;
	double	pixel_size;
	double	half_width;
	double	half_height;
	double	aspect;
	int		is_set;
	t_tuple	position;
	t_tuple	from;
	t_tuple	to;
	t_tuple	up;
	double	**transform;
}	t_camera;

typedef struct s_world
{
	t_camera	camera;
	t_light		light;
	t_object	*objects;
	t_ambient	ambient;
	int			object_count;
}	t_world;

typedef struct s_hit
{
	double		t[2];
	t_tuple		point;
	t_tuple		normal;
	t_object	*obj;
}	t_hit;

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
	t_color	color;
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

// color functions
int			create_trgb(int t, int r, int g, int b);
t_color		create_color(double r, double g, double b);
t_color		color_add(t_color a, t_color b);
t_color		color_scale(t_color c, double factor);
int			color_to_trgb(t_color c);
t_color		lighting(t_world *world, t_ray *ray, t_hit *hit, t_tuple p_eye);
double		clamp(double x);
t_color		background_color(void);
t_color		hit_color(t_world *world, t_ray *ray, t_hit *hit);

// render functions
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		create_img(t_data *data, t_ray ray, int x, int y);
int			render_next_frame(t_data *data);

// event functions
int			mouse_click(int button, int x, int y, t_data *data);
int			key_press(int key, t_data *data);
int			close_window(t_data *data);

// vector functions
double		scalar_product(t_tuple a, t_tuple b);
double		sq_euclidean_distance(t_tuple a, t_tuple b);
double		euclidean_distance(t_tuple a, t_tuple b);
void		vector_add(t_tuple *result, t_tuple a, t_tuple b);
void		vector_neg(t_tuple *result, t_tuple a);
void		vector_diff(t_tuple *result, t_tuple a, t_tuple b);
void		vector_scale(t_tuple *result, t_tuple a, double factor);
void		vector_norm(t_tuple *result, t_tuple a);
void		vector_reflexion(t_tuple *result, t_tuple ray, t_tuple normal);
void		get_points(t_tuple *point, t_tuple ray, t_tuple o_ray, double d[]);
t_tuple		create_tuple(double x, double y, double z);
t_tuple		cross_product(t_tuple a, t_tuple b);

// intersect functions
int			intersect_sphere(t_sphere *sphere, t_ray ray,
				t_hit *out);
int			intersect_plane(t_plane *plane, t_ray ray,
				t_hit *out);
int			intersect_cylinder(t_cylinder *cylinder, t_ray ray,
				t_hit *out);
int			intersect_world(t_world *w, t_ray ray, t_hit *out);
void		swap_min(double *a, double *b);
int			intersect_object(t_object *obj, t_ray ray, t_hit *out);


// camera functions
void		ajust_camera(t_data *data);
t_ray		ray_for_pixel(t_camera camera, int px, int py);
void		set_orientation_matrix(double **orientation, t_tuple left,
				t_tuple true_up, t_tuple forward);
double		**view_transform(t_tuple from, t_tuple to, t_tuple up);

// matrix functions
t_tuple		matrix_mult(double **matrix, t_tuple point);
double		**transpose(double **matrix, int size);
double		**inverse_matrix(double **matrix);
double		**scalar_product_matrix(double **matrix, double scalar);
double		**matrix_mult_4x4(double **matrix_A, double **matrix_B);
double		**allocate_4x4_matrix(void);
double		**translation_matrix(double x, double y, double z);

// inverse matrix helpers
double		**extract_adj(int i, int j, double **matrix);
double		det_adj(int i, int j, double **matrix);
double		det_4x4(double **matrix);
int			extract_adj_assign(int *n, double **matrix, double **adj);

// object functions
t_object	*object_new(t_obj_type type, void *shape, t_color color);
void		object_add(t_object **lst, t_object *new_obj);

// parser functions
int			parse_ambient(char **t, t_world *scene);
int			parse_camera(char **t, t_world *scene);
int			parse_light(char **t, t_world *scene);
int			parse_sphere(char **t, t_world *scene);
int			parse_plane(char **t, t_world *scene);
int			parse_cylinder(char **t, t_world *scene);
int			parse_tuple(const char *s, t_tuple *out);
int			parse_double(const char *str, double *out);
int			parse_color(char *str, t_color *out);
int			parse_line(char *line, t_world *scene);
int			validate_scene(t_world *scene);
int			is_space(char c);
int			parse_sign(const char *s, int *i);
int			parse_int_part(const char *s, int *i, double *res);
int			parse_frac_part(const char *s, int *i, double *res);
int			parse_scene(const char *filename, t_world *scene);

// clean up functions
void		free_nxn_matrix(double **matrix, int n);
void		free_split(char **split);
void		free_world(t_world *world);

// init functions
void		init_scene(t_world *scene);
int			init_data(t_data *data);

#endif
