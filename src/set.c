#include "../include/minirt.h"

void set_colors(char **colors, t_color *color)
{
    set_red(color, ft_atoi(colors[0]));
    set_green(color, ft_atoi(colors[1]));
    set_blue(color, ft_atoi(colors[2]));
}

void set_vec3(char **vec3, t_vec3 *vec)
{
    vec3_set_x(vec, ft_atof(vec3[0]));
    vec3_set_y(vec, ft_atof(vec3[1]));
    vec3_set_z(vec, ft_atof(vec3[2]));
}
