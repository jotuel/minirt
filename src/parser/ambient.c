#include "../../include/minirt.h"

void	validate_ambiance(char *line, t_ambient amb, t_list *lst)
{
	static int nbr;

	if (nbr++)
		ft_error(lst);
	else if (ft_strncmp(ft_strchr(line, 'A'), "A\t", 2))
		ft_error(lst);
	else if (amb.intensity < 0 || amb.intensity > 1)
		ft_error(lst);
}

// A 0.2 255,255,255 example of ambient lighting
t_list	*ambient(char *line, t_list *lst, t_ambient amb)
{
	char	**split;
	char	**colors;

	split = split_and_check(line, '\t', 3, (void *[3]){lst, NULL, line});
	amb.intensity = ft_atof(split[1]);
	colors = split_and_check(split[2], ',', 3, (void *[3]){lst, split, line});
	set_colors(colors, &amb.color);
	free_split(colors);
	free_split(split);
	validate_ambiance(line, amb, lst);
	return (ft_lstnew(obj((t_obj){.ambiance = amb, .type = AMB}, lst)));
}
