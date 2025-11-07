#include "../Include/miniRT.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

void	create_img(t_data *data, t_complex p, int x, int y)
{
	int		color;
/*
    if (p.imagpart  <= 2 && p.imagpart >= -2 && p.realpart  <= 2 && p.realpart >= -2)
    {
	    color = create_trgb(0, 250, 0, 0);
	    my_mlx_pixel_put(data, x, y, color);
    }
    else
    {
	    color = create_trgb(0, 0, 0, 0);
	    my_mlx_pixel_put(data, x, y, color);
    }
*/
	if ( p.imagpart - p.realpart*p.realpart < 0.01 && -p.imagpart + p.realpart*p.realpart < 0.01)
	{
	    color = create_trgb(0, 0, 250, 0);
	    my_mlx_pixel_put(data, x, y, color); (R*cos(a), R*sin(a))
	}
}