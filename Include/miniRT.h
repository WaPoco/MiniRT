/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpogorel <vpogorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:30:17 by vpogorel          #+#    #+#             */
/*   Updated: 2025/11/06 16:56:58 by vpogorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include <stdlib.h>
# include <stdio.h>

typedef struct s_complex
{
	long double	realpart;
	long double	imagpart;	
}	t_complex;

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
	long double	zoom;
	long double	real_min;
	long double	real_max;
	long double	imag_max;
	long double	imag_min;
	long double	fixed_x;
	long double	fixed_y;
	int			fixated;
	char		option;
	int			*t;
	int			**s;
	t_complex	c;
}	t_data;

int			create_trgb(int t, int r, int g, int b);
int			close_window(t_data *data);
//void		click_button(int x, int y, int button, t_data *data);
//int			mouse_click(int button, int x, int y, t_data *data);
//int			key_press(int key, t_data *data);
int			create_trgb(int t, int r, int g, int b);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		create_img(t_data *data, t_complex p, int x, int y);
//int			iteration(t_complex z_0, t_complex c, t_data *data);

#endif
