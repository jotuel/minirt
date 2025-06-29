#include "../../include/minirt.h"

void	validate_light(char *line, t_light light, t_list *lst)
{
	(void)line;
	(void)light;
	(void)lst;
}

// L -40.0,50.0,0.0 0.6 10,0,255
t_list	*light(char *line, t_list *lst, t_light light)
{
	char	**split;
	char	**vec3;
	char	**colors;

	split = split_and_check(line, '\t', 4, (void *[]){lst, NULL, line});
	light.intensity = ft_atof(split[2]);
	vec3 = split_and_check(split[1], ',', 3, (void *[]){lst, split, line});
	set_vec3(vec3, &light.pos);
	free_split(vec3);
	colors = split_and_check(split[3], ',', 3, (void *[]){lst, split, line});
	set_colors(colors, &light.color);
	free_split(colors);
	free_split(split);
	validate_light(line, light, lst);
	return (ft_lstnew(obj((t_obj){.light = light, .type = LIGHT}, lst)));
}
