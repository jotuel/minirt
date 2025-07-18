#include "../include/minirt.h"
#include <float.h>

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

/* TODO: check for alien characters */
void set_colors(char **colors, t_color *color)
{
	unsigned int check;

	check = ft_atoi(colors[0]);
	if (check > 255 && ft_strlen(colors[0]) > 3)
		ft_error(NULL);
    set_red(color, check);
   	check = ft_atoi(colors[1]);
	if (check > 255 && ft_strlen(colors[1]) > 3)
		ft_error(NULL);
    set_green(color, check);
   	check = ft_atoi(colors[2]);
	if (check > 255 && ft_strlen(colors[2]) > 3)
		ft_error(NULL);
    set_blue(color, check);
}

/* TODO: check for alien characters */
void set_vec3(char **vec3, t_vec3 *vec)
{
	double check;

	check = ft_atof(vec3[0]);
	if (check < -FLT_MAX || check > FLT_MAX)
		ft_error(NULL);
    vec3_set_x(vec, check);
   	check = ft_atof(vec3[1]);
	if (check < -FLT_MAX || check > FLT_MAX)
		ft_error(NULL);
    vec3_set_y(vec, check);
   	check = ft_atof(vec3[2]);
	if (check < -FLT_MAX || check > FLT_MAX)
		ft_error(NULL);
    vec3_set_z(vec, check);
}
