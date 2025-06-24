#include "../../include/minirt.h"

bool validate_sphere(char *line, t_sphere sp)
{
    (void)line;
    (void)sp;
    return (true);
}

t_list *sphere(char *line, t_list *lst, t_sphere sp)
{
    char **split;
    char **vec3;
    char **colors;

    split = split_and_check(line, '\t', 4, lst);
    vec3 = split_and_check(split[1], ',', 3, lst);
    colors = split_and_check(split[3], ',', 3, lst);
    set_vec3(vec3, &sp.pos);
    set_colors(colors, &sp.color);
    sp.diameter = ft_atof(split[2]);
    free_split(split);
    free_split(vec3);
    free_split(colors);
    if (validate_sphere(line, sp))
        return (ft_lstnew(obj((t_obj){.sphere = sp, .type = SPHERE}, lst)));
    else
        ft_error(lst);
    return (NULL);
}
