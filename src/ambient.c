#include "../include/minirt.h"

// inline static t_color	color_scale(t_color vec, float scale);

// inline t_color ambient_color(t_map *map, t_color effective_color, t_color ambient_color)
// {
// 	return (mix_colors(effective_color, color_scale(ambient_color, map->ambient->intensity)));
// }

t_color clamp_color(t_color a, t_color b)
{
	t_color	color;
	
	color = a;
	if (a.r > b.r)
		color.r = b.r;
	if (a.g > b.g)
		color.g = b.g;
	if (a.b > b.b)
		color.b = b.b;
	return (color);
}