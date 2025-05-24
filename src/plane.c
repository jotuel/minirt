#include "../include/minirt.h"

bool validate_plane(char *line, t_plane pl)
{
    if (!validate_line(line))
        return (false);
    (void)pl;
    return (true);
}

void plane(char *line, t_map *rt, t_plane pl)
{
    char **split;
    char **vec3;
    char **vec;
    char **colors;

    split = split_and_check(line, '\t', 4, rt->space);
    vec3 = split_and_check(split[1], ',', 3, rt->space);
    vec = split_and_check(split[2], ',', 3, rt->space);
    colors = split_and_check(split[3], ',', 3, rt->space);
    set_vec3(vec3, &pl.pos);
    set_vec3(vec, &pl.orientation);
    set_colors(colors, &pl.color);
    free_split(split);
    free_split(vec3);
    free_split(vec);
    free_split(colors);
    if (validate_plane(line, pl))
        rt->obj[rt->nbr++]->plane = pl;
    else
        ft_error(rt->space);
    rt->obj[rt->nbr]->shape = PLANE;
}
