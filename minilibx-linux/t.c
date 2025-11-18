#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <complex.h>
#include <pthread.h>

#define NUM_THREADS 4

typedef struct s_data {
    void    *mlx;
    void    *win;
    void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    int     win_width;
    int     win_height;
    long double  Zoom;
    long double  real_min;
    long double  real_max;
    long double  imag_max;
    long double  imag_min;
    long double  fixed_x;
    long double  fixed_y;
    int          fixated;
}              t_data;

typedef struct s_thread_data {
    t_data *data;
    int start;
    int end;
} t_thread_data;

complex c = -0.25 - 0.5 * I;

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

// Optimized Escape Condition
int iteration(complex z_0, complex c)
{
    int i = 0;
    double real = creal(z_0);
    double imag = cimag(z_0);
    double real2, imag2;

    while (i < 700)
    {
        real2 = real * real;
        imag2 = imag * imag;

        if (real2 + imag2 >= 4.0)
            return create_trgb(0, (i * 2) % 256, (i * 2) % 256, (i * 20) % 256);

        imag = 2 * real * imag + cimag(c);
        real = real2 - imag2 + creal(c);
        i++;
    }

    return create_trgb(0, 0, 0, 0);
}

// Multi-threaded rendering
void *render_section(void *arg)
{
    t_thread_data *td = (t_thread_data *)arg;
    t_data *data = td->data;

    long double dx = (data->real_max - data->real_min) / data->win_width;
    long double dy = (data->imag_max - data->imag_min) / data->win_height;

    for (int i = td->start; i < td->end; i++)
    {
        for (int j = 0; j < data->win_width; j++)
        {
            long double real = data->real_min + j * dx;
            long double imag = data->imag_max - i * dy;
            complex p = real + imag * I;
            int color = iteration(p, 0);
            my_mlx_pixel_put(data, j, i, color);
        }
    }
    return NULL;
}

int render_next_frame(t_data *data)
{
    mlx_clear_window(data->mlx, data->win);
    pthread_t threads[NUM_THREADS];
    t_thread_data td[NUM_THREADS];

    int chunk = data->win_height / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++)
    {
        td[i].data = data;
        td[i].start = i * chunk;
        td[i].end = (i == NUM_THREADS - 1) ? data->win_height : (i + 1) * chunk;
        pthread_create(&threads[i], NULL, render_section, &td[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    return (0);
}

// Fix Zoom Centered on a Point
int mouse_click_hook(int button, int x, int y, t_data *data)
{
    if (button == 1) // Left Click to Fix Point
    {
        data->fixed_x = data->real_min + (data->real_max - data->real_min) * (x / (double)data->win_width);
        data->fixed_y = data->imag_max - (data->imag_max - data->imag_min) * (y / (double)data->win_height);
        data->fixated = 1;
    }

    if ((button == 4 || button == 5) && data->fixated)
    {
        long double zoom_factor = (button == 4) ? 0.9 : 1.1;
        long double width = (data->real_max - data->real_min) * zoom_factor;
        long double height = (data->imag_max - data->imag_min) * zoom_factor;

        data->real_min = data->fixed_x - width / 2;
        data->real_max = data->fixed_x + width / 2;
        data->imag_min = data->fixed_y - height / 2;
        data->imag_max = data->fixed_y + height / 2;
        data->Zoom *= zoom_factor;
    }
    return (0);
}

// Handle Window Resizing
int handle_resize(int new_width, int new_height, t_data *data)
{
    data->win_width = new_width;
    data->win_height = new_height;

    // Update the image to match new window size
    mlx_destroy_image(data->mlx, data->img);
    data->img = mlx_new_image(data->mlx, data->win_width, data->win_height);
    data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);

    return (0);
}

// Handle Keyboard Input
int handle_keypress(int keycode, t_data *data)
{
    long double move_factor = (data->real_max - data->real_min) * 0.1;

    if (keycode == 65307)
        mlx_destroy_window(data->mlx, data->win);

    if (keycode == 119) data->imag_min += move_factor, data->imag_max += move_factor;
    if (keycode == 115) data->imag_min -= move_factor, data->imag_max -= move_factor;
    if (keycode == 97)  data->real_min -= move_factor, data->real_max -= move_factor;
    if (keycode == 100) data->real_min += move_factor, data->real_max += move_factor;

    if (keycode == 65361) c -= 0.01;
    if (keycode == 65363) c += 0.01;
    if (keycode == 65362) c += 0.01 * I;
    if (keycode == 65364) c -= 0.01 * I;

    return (0);
}

int main(void)
{
    t_data data;
    data.win_width = 1000;
    data.win_height = 1000;
    data.Zoom = 1;
    data.real_min = -2;
    data.real_max = 2;
    data.imag_min = -2;
    data.imag_max = 2;
    data.fixated = 0;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, data.win_width, data.win_height, "Resizable Julia Set");
    data.img = mlx_new_image(data.mlx, data.win_width, data.win_height);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

    mlx_hook(data.win, 2, 1L << 0, handle_keypress, &data);
    mlx_hook(data.win, 4, 1L << 2, mouse_click_hook, &data);
    mlx_hook(data.win, 25, 1L << 18, (void *)handle_resize, &data);
    mlx_loop_hook(data.mlx, render_next_frame, &data);
    
    mlx_loop(data.mlx);
    return (0);
}
