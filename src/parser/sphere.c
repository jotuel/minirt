/* ************************************************************************** */
/*                                                                            */
/*                                                     __     h  _ _  _| _    */
/*   sphere.c                                       __/ \\__  i (_(_)(_|(/_   */
/*                                                // \\__/ \\ v  _ _|_        */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>      \\__/ \\__/ e _>(_| | --    */
/*                                                // \\__/ \\ .  _  _ |       */
/*   Created: 2025/07/30 19:17:21 by ehaanpaa     \\__/ \\__/ f (_)(_)|       */
/*   Updated: 2025/07/30 19:17:21 by ehaanpaa        \\__/    i               */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include <stdbool.h>

/*
 * checks for extra characters after sp, whether diameter
 * exists and color values are in range
 */
void	validate_sphere(char *line, t_sphere sp, t_list *lst, bool check)
{
	if (ft_strncmp(ft_strchr(line, 's'), "sp\t", 3))
		ft_error2(&lst, line, "sp: Extra characters");
	else if (sp.radius <= 0)
		ft_error2(&lst, line, "sp: Diameter out of range");
	else if (!check)
		ft_error2(&lst, line, "sp: Color value out of range");
}

/*
 * sp pos x,y,z diameter color r,g,b
 */
t_list	*sphere(char *line, t_list *lst, t_sphere sp)
{
	char	**split;
	char	**tmp;
	bool	check;

	split = split_and_check(line, '\t', 4, (void *[]){lst, NULL, line});
	sp.radius = ft_atof(split[2]);
	tmp = split_and_check(split[1], ',', 3, (void *[]){lst, split, line});
	set_vec3(tmp, &sp.pos);
	free_split(tmp);
	tmp = split_and_check(split[3], ',', 3, (void *[]){lst, split, line});
	check = set_colors(tmp, &sp.color);
	free_split(tmp);
	free_split(split);
	validate_sphere(line, sp, lst, check);
	return (ft_lstnew(obj((t_obj){.sphere = sp, .type = SPH}, lst)));
}
