#include "../include/minirt.h"

bool validate_orientation(t_vec3 orien)
{
    if (orien.x > 1. || orien.x < 0.)
        return (false);
    else if (orien.y > 1. || orien.y < 0.)
        return (false);
    else if (orien.z > 1. || orien.z < 0.)
        return (false);
    return (true);
}

bool validate_line(char *line)
{
    char *res;

    res = ft_strtrim(line, "ACLsplcy0123456789.,\t");
    if (res[0] == '\n')
        return (free(res), true);
    else
        return (free(res), false);
}

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

char **split_and_check(char *input, char by, int fields, void *mem)
{
    char **split;

    split = ft_split(input, by);
    if (!split)
        ft_error(mem);
    if (split[fields])
        ft_error(mem);
    while(fields--)
    {
        if(!split[fields])
            ft_error(mem);
    }
    return (split);
}
