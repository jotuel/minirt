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

/*
 * checking whether color is in range and whether it has extra things
 * if not then setting the value.
 */
bool	set_colors(char **colors, t_color *color)
{
	unsigned int	check;

	check = ft_atoi(colors[0]);
	if (check > 255 || ft_strlen(colors[0]) > 3 || has_alphabet(colors[0]))
		return (false);
	set_red(color, check);
	check = ft_atoi(colors[1]);
	if (check > 255 || ft_strlen(colors[1]) > 3 || has_alphabet(colors[1]))
		return (false);
	set_green(color, check);
	check = ft_atoi(colors[2]);
	if (check > 255 || ft_strlen(colors[2]) > 3 || has_alphabet(colors[2]))
		return (false);
	set_blue(color, check);
	return (true);
}

/*
 * kind of trusting that the float overflows to inf here and setting
 * it to NaN if there are any extra characters which is easy to then
 * check later.
*/
void	set_vec3(char **vec3, t_vec3 *vec)
{
	if (has_alphabet(vec3[0]))
		set_x(vec, -1.f);
	else
		set_x(vec, ft_atof(vec3[0]));
	if (has_alphabet(vec3[1]))
		set_y(vec, -1.f);
	else
		set_y(vec, ft_atof(vec3[1]));
	if (has_alphabet(vec3[2]))
		set_x(vec, -1.f);
	else
		set_z(vec, ft_atof(vec3[2]));
}
