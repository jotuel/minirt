#include "../../include/minirt.h"

void validate_cylinder(char *line, t_cylinder cy, t_list *lst)
{
 	(void)line;
    (void)cy;
    (void)lst;
}

t_list *cylinder(char *line, t_list *lst, t_cylinder cy)
{
    char **split;
    char **vec3;
    char **colors;

    split = split_and_check(line, '\t', 6, (void *[]){lst, NULL, line});
    vec3 = split_and_check(split[1], ',', 3, (void *[]){lst, split, line});
    set_vec3(vec3, &cy.pos);
    free_split(vec3);
    vec3 = split_and_check(split[2], ',', 3, (void *[]){lst, split, line});
    set_vec3(vec3, &cy.orientation);
    free_split(vec3);
    colors = split_and_check(split[5], ',', 3, (void *[]){lst, split, line});
    set_colors(colors, &cy.color);
    cy.diameter = ft_atof(split[3]);
    cy.height = ft_atof(split[4]);
    free_split(split);
    free_split(colors);
    validate_cylinder(line, cy, lst);
    return (ft_lstnew(obj((t_obj){.cylinder = cy, .type = CYLINDER}, lst)));
}
