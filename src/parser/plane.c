#include "../../include/minirt.h"

bool validate_plane(char *line, t_plane pl)
{
    (void)line;
    (void)pl;
    return (true);
}

t_list *plane(char *line, t_list *lst, t_plane pl)
{
    char **split;
    char **vec3;
    char **vec;
    char **colors;

    split = split_and_check(line, '\t', 4, lst);
    vec3 = split_and_check(split[1], ',', 3, lst);
    vec = split_and_check(split[2], ',', 3, lst);
    colors = split_and_check(split[3], ',', 3, lst);
    set_vec3(vec3, &pl.pos);
    set_vec3(vec, &pl.orientation);
    set_colors(colors, &pl.color);
    free_split(split);
    free_split(vec3);
    free_split(vec);
    free_split(colors);
    if (validate_plane(line, pl))
        return (ft_lstnew(obj((t_obj){.plane = pl, .type = PLANE}, lst)));
    else
        ft_error(lst);
    return (NULL);
}
