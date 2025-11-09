#include "../Include/miniRT.h"

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_display(data->mlx);
	exit(1);
	return (0);
}

static int	render_next_frame(t_data *data)
{
	long double	d[2];
	int			i;
	int			k;
	t_tuple	p;

	d[0] = (data->real_max - data->real_min) / data->win_width;
	d[1] = (data->imag_max - data->imag_min) / data->win_height;
	i = 0;
	while (i < data->win_width)
	{
		k = 0;
		while (k < data->win_height)
		{
			p.x = data->real_min + d[0] * i;
			p.y = data->imag_max - d[1] * k;
			p.z = 5;
			create_img(data, p, i, k);
			k++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
/*(data->t[2]) % 256
static void	show_options(t_data *data, int args0, char **args)
{
	if ((args0 == 2) && (ft_strlen(args[1]) == 1) 
		&& (args[1][0] == '1' || args[1][0] == '2' || args[1][0] == '3'))
	{
		data->option = args[1][0];
		if (data->option == '1')
		{
			data->c.realpart = 0;
			data->c.imagpart = 0;
		}
		else if (data->option == '2')
		{
			data->c.realpart = 0.5;
			data->c.imagpart = 0.55;
		}
		else if (data->option == '3')
		{
			data->c.realpart = 0;
			data->c.imagpart = -1;
		}
		return ;
	}
	ft_printf("Choose a fractal!\n1: Mandelbrot \n");
	ft_printf("2: Turtle \n3: Island c=(0,-1)\n");
	exit(1);
}
*/

int	main(int args0, char **args)
{
	t_data	data;
    (void)args0;
    (void)args;
	//error_init_style(&data);
	//show_options(&data, args0, args);
	data.win_height = 750;
	data.win_width = 750;
	data.real_min = -4;
	data.real_max = 4;
	data.imag_max = 4;
	data.imag_min = -4;
	data.zoom = 1;
	//data.t = style(&data);
	data.fixated = 0;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.win_width, data.win_height,
			"MiniRT");
	data.img = mlx_new_image(data.mlx, data.win_width, data.win_height);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	//mlx_hook(data.win, 2, 1L << 0, key_press, &data);
	//mlx_hook(data.win, 4, 1L << 2, mouse_click, &data);
	mlx_hook(data.win, 17, 1L << 17, close_window, &data);
	mlx_loop_hook(data.mlx, render_next_frame, &data);
	mlx_loop(data.mlx);
	return (0);
}