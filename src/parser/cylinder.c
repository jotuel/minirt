#include "../../include/minirt.h"

/*
 * checks for extra characters after cy, that diameter and
 * height exist and that orientation is a valid unit vector.
 */
void	validate_cylinder(char *line, t_cylinder cy, t_list *lst)
{
	if (ft_strncmp(ft_strchr(line, 'c'), "cy\t", 3))
		ft_error2(&lst, line, "cy: Extra characters");
	else if (cy.radius < 0 || cy.height < 0)
		ft_error2(&lst, line, "cy: diameter or height out of range");
	else if (0 == dot(cy.orientation, cy.orientation))
		ft_error2(&lst, line, "cy: Not a unit vector");
}

/*
 * cy pos x,y,z unit vector u,v,w diameter height color
 */
t_list	*cylinder(char *line, t_list *lst, t_cylinder cy)
{
	char	**split;
	char	**tmp;

	split = split_and_check(line, '\t', 6, (void *[]){lst, NULL, line});
	tmp = split_and_check(split[1], ',', 3, (void *[]){lst, split, line});
	set_vec3(tmp, &cy.pos);
	free_split(tmp);
	tmp = split_and_check(split[2], ',', 3, (void *[]){lst, split, line});
	set_vec3(tmp, &cy.orientation);
	free_split(tmp);
	tmp = split_and_check(split[5], ',', 3, (void *[]){lst, split, line});
	set_colors(tmp, &cy.color);
	cy.radius = ft_atof(split[3]);
	cy.height = ft_atof(split[4]);
	free_split(split);
	free_split(tmp);
	validate_cylinder(line, cy, lst);
	return (ft_lstnew(obj((t_obj){.cylinder = cy, .type = CYL}, lst)));
}
