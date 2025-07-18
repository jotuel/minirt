#include "../../include/minirt.h"

void	validate_cylinder(char *line, t_cylinder cy, t_list *lst)
{
	if (ft_strncmp(ft_strchr(line, 'c'), "cy\t", 3))
		ft_error(lst);
	else if (cy.diameter < 0 || cy.height < 0)
		ft_error(lst);
	else if (0 == vec3_dot(cy.orientation, cy.orientation))
		ft_error(lst);
}

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
	cy.diameter = ft_atof(split[3]);
	cy.height = ft_atof(split[4]);
	free_split(split);
	free_split(tmp);
	validate_cylinder(line, cy, lst);
	return (ft_lstnew(obj((t_obj){.cylinder = cy, .type = CYL}, lst)));
}
