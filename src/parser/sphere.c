#include "../../include/minirt.h"

void	validate_sphere(char *line, t_sphere sp, t_list *lst)
{
	if (ft_strncmp(ft_strchr(line, 's'), "sp\t", 3))
		ft_error(lst);
	else if (sp.radius < 0)
		ft_error(lst);
}

t_list	*sphere(char *line, t_list *lst, t_sphere sp)
{
	char	**split;
	char	**tmp;

	split = split_and_check(line, '\t', 4, (void *[]){lst, NULL, line});
	sp.radius = ft_atof(split[2]);
	tmp = split_and_check(split[1], ',', 3, (void *[]){lst, split, line});
	set_vec3(tmp, &sp.pos);
	free_split(tmp);
	tmp = split_and_check(split[3], ',', 3, (void *[]){lst, split, line});
	set_colors(tmp, &sp.color);
	free_split(tmp);
	free_split(split);
	validate_sphere(line, sp, lst);
	return (ft_lstnew(obj((t_obj){.sphere = sp, .type = SPH}, lst)));
}
