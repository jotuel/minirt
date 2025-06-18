#include "../../include/minirt.h"

bool validate_light(char *line, t_light light)
{
    (void)line;
    (void)light;
    return (true);
}

// L -40.0,50.0,0.0 0.6 10,0,255
void light(char *line, t_list *lst, t_light light)
{
    char **split;
    char **vec3;
    char **colors;

    split = split_and_check(line, '\t', 4, lst);
    vec3 = split_and_check(split[1], ',', 3, lst);
    colors = split_and_check(split[3], ',', 3, lst);
    set_vec3(vec3, &light.pos);
    set_colors(colors, &light.color);
    light.intensity = ft_atof(split[2]);
    free_split(split);
    free_split(vec3);
    free_split(colors);
    if (validate_light(line, light))
    	ft_lstadd_front(&lst, ft_lstnew(&light));
    else
        ft_error(lst);
}
