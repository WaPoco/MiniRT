/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:30:17 by vpogorel          #+#    #+#             */
/*   Updated: 2025/11/12 12:32:15 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

typedef struct s_tuple
{
	double	x;
	double	y;
	double  z;
	int		type;	
}	t_tuple;

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
	double	zoom;
	double	real_min;
	double	real_max;
	double	imag_max;
	double	imag_min;
	double	fixed_x;
	double	fixed_y;
	int			fixated;
	char		option;
	int			*t;
	int			**s;
	t_tuple		c;
}	t_data;

int			create_trgb(int t, int r, int g, int b);
int			close_window(t_data *data);
//void		click_button(int x, int y, int button, t_data *data);
//int			mouse_click(int button, int x, int y, t_data *data);
//int			key_press(int key, t_data *data);
int			create_trgb(int t, int r, int g, int b);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		create_img(t_data *data, t_tuple p, int x, int y);
double		scalar_product(t_tuple a, t_tuple b);
t_tuple  	*int_section(t_tuple ray, t_tuple o_ray, t_tuple c_sphere, double r_sphere);
double 		sq_euclidean_distance(t_tuple a, t_tuple b);
double		euclidean_distance(t_tuple a, t_tuple b);
void		vector_add(t_tuple *result, t_tuple a, t_tuple b);
void		vector_neg(t_tuple *result, t_tuple a);
void 		vector_diff(t_tuple *result, t_tuple a, t_tuple b);
void 		vector_reflexion(t_tuple *result, t_tuple ray, t_tuple normal);
void 		vector_scale(t_tuple *result, t_tuple a, double factor);
void 		vector_norm(t_tuple *result, t_tuple a);
void    	get_points(t_tuple *P, t_tuple ray, t_tuple o_ray, double d[]);
double    	lighting(t_tuple ray, t_tuple p_light, t_tuple point, t_tuple p_eye, t_tuple normalv);

//int			iteration(t_complex z_0, t_complex c, t_data *data);

#endif
