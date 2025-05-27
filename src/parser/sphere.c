#include "../../include/minirt.h"

bool validate_sphere(char *line, t_sphere sp)
{
    (void)line;
    (void)sp;
    return (true);
}

void sphere(char *line, t_map *rt, t_sphere sp)
{
    char **split;
    char **vec3;
    char **colors;

    split = split_and_check(line, '\t', 4, rt->space);
    vec3 = split_and_check(split[1], ',', 3, rt->space);
    colors = split_and_check(split[3], ',', 3, rt->space);
    set_vec3(vec3, &sp.pos);
    set_colors(colors, &sp.color);
    sp.diameter = ft_atof(split[2]);
    free_split(split);
    free_split(vec3);
    free_split(colors);
    if (validate_sphere(line, sp))
        rt->obj[rt->nbr++]->sphere = sp;
    else
        ft_error(rt->space);
    rt->obj[rt->nbr]->shape = SPHERE;
}
