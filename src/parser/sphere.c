#include "../../include/minirt.h"

void validate_sphere(char *line, t_sphere sp, t_list *lst)
{
    (void)line;
    (void)sp;
    (void)lst;
}

t_list *sphere(char *line, t_list *lst, t_sphere sp)
{
    char **split;
    char **vec3;
    char **colors;

    split = split_and_check(line, '\t', 4, (void *[]){lst, NULL, line});
    sp.diameter = ft_atof(split[2]);
    vec3 = split_and_check(split[1], ',', 3, (void *[]){lst, split, line});
    set_vec3(vec3, &sp.pos);
    free_split(vec3);
    colors = split_and_check(split[3], ',', 3, (void *[]){lst, split, line});
    set_colors(colors, &sp.color);
    free_split(colors);
    free_split(split);
    validate_sphere(line, sp, lst);
    return (ft_lstnew(obj((t_obj){.sphere = sp, .type = SPHERE}, lst)));
}
