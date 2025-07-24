#include "../../include/minirt.h"

/*
 * checks that only one exists, after A character there is no extra,
 * that intensity is withing range and color values are in range
 */
void	validate_ambiance(char *line, t_ambient amb, t_list *lst, bool check)
{
	static int	nbr;

	if (nbr++)
		ft_error2(&lst, line, "Only one ambiance");
	else if (ft_strncmp(ft_strchr(line, 'A'), "A\t", 2))
		ft_error2(&lst, line, "A: Extra characters");
	else if (amb.intensity < 0 || amb.intensity > 1)
		ft_error2(&lst, line, "A: Intensity out of range");
	else if (!check)
		ft_error2(&lst, line, "A: Color out of range");
}

// A 0.2 255,255,255 example of ambient lighting
t_list	*ambient(char *line, t_list *lst, t_ambient amb)
{
	char	**split;
	char	**colors;
	bool	check;

	split = split_and_check(line, '\t', 3, (void *[3]){lst, NULL, line});
	amb.intensity = ft_atof(split[1]);
	colors = split_and_check(split[2], ',', 3, (void *[3]){lst, split, line});
	check = set_colors(colors, &amb.color);
	free_split(colors);
	free_split(split);
	validate_ambiance(line, amb, lst, check);
	return (ft_lstnew(obj((t_obj){.ambiance = amb, .type = AMB}, lst)));
}
