#include "../../include/minirt.h"

/*
 * checks for extra characters after pl and that normal
 * is a valid unit vector.
 */
void	validate_plane(char *line, t_plane pl, t_list *lst)
{
	if (ft_strncmp(ft_strchr(line, 'p'), "pl\t", 3))
		ft_error2(&lst, line, "pl: Extra characters");
	else if (0 == dot(pl.orientation, pl.orientation))
		ft_error2(&lst, line, "pl: Not a unit vector");
}

/*
 * pl pos x,y,z normal as unit vector u,v,w, color r,g,b
 */
t_list	*plane(char *line, t_list *lst, t_plane pl)
{
	char	**split;
	char	**tmp;

	split = split_and_check(line, '\t', 4, (void *[]){lst, NULL, line});
	tmp = split_and_check(split[1], ',', 3, (void *[]){lst, split, line});
	set_vec3(tmp, &pl.pos);
	free_split(tmp);
	tmp = split_and_check(split[2], ',', 3, (void *[]){lst, split, line});
	set_vec3(tmp, &pl.orientation);
	free_split(tmp);
	tmp = split_and_check(split[3], ',', 3, (void *[]){lst, split, line});
	set_colors(tmp, &pl.color);
	free_split(tmp);
	free_split(split);
	validate_plane(line, pl, lst);
	return (ft_lstnew(obj((t_obj){.plane = pl, .type = PLANE}, lst)));
}
