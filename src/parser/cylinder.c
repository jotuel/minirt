#include "../../include/minirt.h"

bool validate_cylinder(char *line, t_cylinder cy)
{
 	(void)line;
    (void)cy;
    return (true);
}

t_list *cylinder(char *line, t_list *lst, t_cylinder cy)
{
    char **split;
    char **vec3;
    char **vec;
    char **colors;

    split = split_and_check(line, '\t', 6, lst);
    vec3 = split_and_check(split[1], ',', 3, lst);
    vec = split_and_check(split[2], ',', 3, lst);
    colors = split_and_check(split[5], ',', 3, lst);
    set_vec3(vec3, &cy.pos);
    set_vec3(vec, &cy.orientation);
    set_colors(colors, &cy.color);
    cy.diameter = ft_atof(split[3]);
    cy.height = ft_atof(split[4]);
    free_split(split);
    free_split(vec3);
    free_split(vec);
    free_split(colors);
    if (validate_cylinder(line, cy))
       	return (ft_lstnew(&(t_obj){.cylinder = cy, .type = CYLINDER}));
    else
        ft_error(lst);
    return (NULL);
}
