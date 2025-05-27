#include "../include/minirt.h"

bool validate_cylinder(char *line, t_cylinder cy)
{
    if (!validate_line(line))
        return (false);
    (void)cy;
    return (true);
}

void cylinder(char *line, t_map *rt, t_cylinder cy)
{
    char **split;
    char **vec3;
    char **vec;
    char **colors;

    split = split_and_check(line, '\t', 6, rt->space);
    vec3 = split_and_check(split[1], ',', 3, rt->space);
    vec = split_and_check(split[2], ',', 3, rt->space);
    colors = split_and_check(split[5], ',', 3, rt->space);
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
        rt->obj[rt->nbr++]->cylinder = cy;
    else
        ft_error(rt->space);
    rt->obj[rt->nbr]->type = CYLINDER;
}
