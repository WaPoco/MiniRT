#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <complex.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define SUPERSAMPLE_FACTOR 2 // 2x supersampling


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int	close(int keycode, t_vars *vars)
{
	if (0xff1b == keycode)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		return (0);
	}
	return (0);
}
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int iteration(complex z_0, complex c)
{
    int i = 0;
    double magnitude;

    while (i < 20)
    {
        z_0 = z_0 * z_0 + c;
        magnitude = cabs(z_0); // Compute magnitude (distance from origin)
        if (magnitude >= 2)
        {
            // Generate color based on the iteration count
            int r = (i*2) % 256;   // Red component
            int g = (i* 2) % 256;   // Green component
            int b = (i* 20) % 256;  // Blue component
			//printf("interation = %d \n", i);
            return create_trgb(0, r, g, b); // Combine into color
        }
        i++;
    }

    // Return black for points that do not escape
    return create_trgb(0, 0, 0, 0);
}

int	main(void)
{
	t_data	img;
	t_vars	vars;
	//int		i;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1000, 1000, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 1000, 1000);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, 
								&img.endian);
	//int image_width = 1500;
	//int image_height = 1500;
	//i = 0;
	/*
	while (i++ < 50000)
		my_mlx_pixel_put(&img,400 + 100*cos(2*M_PI*100*i / 50000),400 - 100 * sin(2*M_PI*100*i / 50000), 0x00FF0000);
	i = 0;
	while (i++ < 50000)
		my_mlx_pixel_put(&img,400 + 10*cos(2*M_PI*10*i / 50000),400 - 10 * sin(2*M_PI*10*i / 50000), create_trgb(10,100,230, 20));
	*/
	double n = 2000.0;
	double real_min = -2, real_max = 2;
	double imag_min = -2, imag_max = 2;
	double dx = (real_max - real_min) / n; // 1000 is the image width
	double dy = (imag_max - imag_min) / n; // 1000 is the image height

	for (int i = 0; i < (int)n; i++)
	{
		for (int j = 0; j < (int)n; j++)
		{
			double real = real_min + j * dx;
			double imag = imag_max - i * dy; // Flip vertically
			complex p = real + imag * I;
			int color = iteration(0, p);
			my_mlx_pixel_put(&img, (1000.0/n)*j, (1000.0/n)*i, color);
		}
	}
	/*
	int supersample_width = image_width * SUPERSAMPLE_FACTOR;
	int supersample_height = image_height * SUPERSAMPLE_FACTOR;

	double real_min = -2, real_max = -2;
	double imag_min = -2, imag_max = 2;

	double dx = (real_max - real_min) / supersample_width;
	double dy = (imag_max - imag_min) / supersample_height;

	for (int i = 0; i < image_height; i++) {
		for (int j = 0; j < image_width; j++) {
			int r = 0, g = 0, b = 0;
			double real = 0.0, imag = 0.0;

			// Supersampling loop
			for (int si = 0; si < SUPERSAMPLE_FACTOR; si++) {
				for (int sj = 0; sj < SUPERSAMPLE_FACTOR; sj++) {
					real = real_min + ((j * SUPERSAMPLE_FACTOR + sj) * dx);
					imag = imag_max - ((i * SUPERSAMPLE_FACTOR + si) * dy);
					complex p = real + imag * I;
					int color = iteration(0, p);

					// Extract RGB components
					r += (color >> 16) & 0xFF; // Red
					g += (color >> 8) & 0xFF;  // Green
					b += color & 0xFF;         // Blue
				}
			}

			// Compute average color
			r /= (SUPERSAMPLE_FACTOR * SUPERSAMPLE_FACTOR);
			g /= (SUPERSAMPLE_FACTOR * SUPERSAMPLE_FACTOR);
			b /= (SUPERSAMPLE_FACTOR * SUPERSAMPLE_FACTOR);

			// Combine averaged color and plot it
			int avg_color = create_trgb(0, r, g, b);
			my_mlx_pixel_put(&img, 500 + 250 * real, 500 - 250 * imag, avg_color);
		}
	}*/
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 2, 1L<<0, close, &vars);
	mlx_loop(vars.mlx);
}
