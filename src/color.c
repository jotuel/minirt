#include "../include/minirt.h"
#include <stdint.h>

void	set_colors(char **colors, t_color *color)
{
	set_red(color, ft_atoi(colors[0]));
	set_green(color, ft_atoi(colors[1]));
	set_blue(color, ft_atoi(colors[2]));
}

void	set_red(t_color *color, uint8_t colour)
{
	color->r = colour;
}

void	set_green(t_color *color, uint8_t colour)
{
	color->g = colour;
}

void	set_blue(t_color *color, uint8_t colour)
{
	color->b = colour;
}

t_color	mix_colors(t_color color1, t_color color2)
{
	int	r;
	int	g;
	int	b;

	r = (color1.r + color2.r) / 2;
	g = (color1.g + color2.g) / 2;
	b = (color1.b + color2.b) / 2;
	return ((t_color){r, g, b});
}

inline uint_fast32_t	get_color(t_color color)
{
	return ((color.r << 24) + (color.g << 16) + (color.b << 8) + 255);
}
