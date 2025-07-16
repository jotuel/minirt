#include "../include/minirt.h"
#include <stdint.h>

t_color	add_colors(t_color color1, t_color color2)
{
	int	r;
	int	g;
	int	b;

	r = ((int)color1.r + (int)color2.r);
	g = ((int)color1.g + (int)color2.g);
	b = ((int)color1.b + (int)color2.b);
	r = fmin(r, 255);
	g = fmin(g, 255);
	b = fmin(b, 255);
	return ((t_color){r, g, b});
}

t_color	mix_colors(t_color color1, t_color color2)
{
	int	r;
	int	g;
	int	b;

	r = ((int)color1.r + (int)color2.r)/2;
	g = ((int)color1.g + (int)color2.g)/2;
	b = ((int)color1.b + (int)color2.b)/2;
	return ((t_color){r, g, b});
}

inline uint_fast32_t	get_color(t_color color)
{
	return ((color.r << 24) + (color.g << 16) + (color.b << 8) + 255);
}
