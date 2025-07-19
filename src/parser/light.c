#include "../../include/minirt.h"

void	validate_light(char *line, t_light light, t_list *lst)
{
	static int nbr;

	if (nbr++)
		ft_error(lst);
	else if (ft_strncmp(ft_strchr(line, 'L'), "L\t", 2))
		ft_error(lst);
	else if (light.intensity < 0 || light.intensity > 1)
		ft_error(lst);
}

// L -40.0,50.0,0.0 0.6 10,0,255
t_list	*light(char *line, t_list *lst, t_light light)
{
	char	**split;
	char	**tmp;

	split = split_and_check(line, '\t', 4, (void *[]){lst, NULL, line});
	light.intensity = ft_atof(split[2]);
	tmp = split_and_check(split[1], ',', 3, (void *[]){lst, split, line});
	set_vec3(tmp, &light.pos);
	free_split(tmp);
	tmp = split_and_check(split[3], ',', 3, (void *[]){lst, split, line});
	set_colors(tmp, &light.color);
	free_split(tmp);
	free_split(split);
	validate_light(line, light, lst);
	return (ft_lstnew(obj((t_obj){.light = light, .type = LIGHT}, lst)));
}
