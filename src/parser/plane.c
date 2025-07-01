#include "../../include/minirt.h"

void	validate_plane(char *line, t_plane pl, t_list *lst)
{
	(void)line;
	(void)pl;
	(void)lst;
}

t_list	*plane(char *line, t_list *lst, t_plane pl)
{
	char	**split;
	char	**vec3;
	char	**colors;

	split = split_and_check(line, '\t', 4, (void *[]){lst, NULL, line});
	vec3 = split_and_check(split[1], ',', 3, (void *[]){lst, split, line});
	set_vec3(vec3, &pl.pos);
	free_split(vec3);
	vec3 = split_and_check(split[2], ',', 3, (void *[]){lst, split, line});
	set_vec3(vec3, &pl.orientation);
	free_split(vec3);
	colors = split_and_check(split[3], ',', 3, (void *[]){lst, split, line});
	set_colors(colors, &pl.color);
	free_split(colors);
	free_split(split);
	validate_plane(line, pl, lst);
	return (ft_lstnew(obj((t_obj){.plane = pl, .type = PLANE}, lst)));
}
