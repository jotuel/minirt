#include "../include/minirt.h"

static bool validate_ambiance(char *line, t_ambient amb)
{
    (void)line;
    (void)amb;
    return (true);
}

// A 0.2 255,255,255 example of ambient lighting
void ambient(char *line, t_map *rt, t_ambient amb)
{
    char **split;
    char **colors;

    split = split_and_check(line, '\t', 4, rt->space);
    amb.intensity = ft_atof(split[1]);
    colors = split_and_check(split[2], ',', 3, rt->space);
    set_colors(colors, &amb.color);
    free_split(split);
    free_split(colors);
    if (validate_ambiance(line, amb))
        rt->obj[rt->nbr++]->ambiance = amb;
    else
        ft_error(rt->space);
    rt->obj[rt->nbr]->type = AMBIENT;
}
