#include "../../include/minirt.h"

static bool validate_ambiance(char *line, t_ambient amb)
{
    (void)line;
    (void)amb;
    return (true);
}

// A 0.2 255,255,255 example of ambient lighting
t_list *ambient(char *line, t_list *lst, t_ambient amb)
{
    char **split;
    char **colors;

    split = split_and_check(line, '\t', 3, lst);
    amb.intensity = ft_atof(split[1]);
    colors = split_and_check(split[2], ',', 3, lst);
    set_colors(colors, &amb.color);
    free_split(split);
    free_split(colors);
    if (validate_ambiance(line, amb))
       	return (ft_lstnew(&(t_obj){.ambiance = amb, .type = AMBIENT}));
    else
        ft_error(lst);
    return (NULL);
}
