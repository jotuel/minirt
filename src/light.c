#include "../include/minirt.h"

bool validate_light(char *line, t_light light)
{
    if (!validate_line(line))
        return (false);
    (void)light;
    return (true);
}

void light(char *line, t_map *rt, t_light light)
{
    char **split;
    char **vec3;
    char **colors;

    split = split_and_check(line, '\t', 4, rt->space);
    vec3 = split_and_check(split[1], ',', 3, rt->space);
    colors = split_and_check(split[3], ',', 3, rt->space);
    set_vec3(vec3, &light.pos);
    set_colors(colors, &light.color);
    light.range = ft_atof(split[2]);
    free_split(split);
    free_split(vec3);
    free_split(colors);
    if (validate_light(line, light))
        rt->obj[rt->nbr++]->light = light;
    else
        ft_error(rt->space);
    rt->obj[rt->nbr]->shape = LIGHT;
}
