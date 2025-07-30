/* ************************************************************************** */
/*                                                                            */
/*                                                     __     h  _ _  _| _    */
/*   utils.c                                        __/ \\__  i (_(_)(_|(/_   */
/*                                                // \\__/ \\ v  _ _|_        */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>      \\__/ \\__/ e _>(_| | --    */
/*                                                // \\__/ \\ .  _  _ |       */
/*   Created: 2025/07/30 19:17:26 by ehaanpaa     \\__/ \\__/ f (_)(_)|       */
/*   Updated: 2025/07/30 19:17:26 by ehaanpaa        \\__/    i               */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

bool	validate_orientation(t_vec3 orien)
{
	if (orien.x > 1. || orien.x < -1.)
		return (false);
	else if (orien.y > 1. || orien.y < -1.)
		return (false);
	else if (orien.z > 1. || orien.z < -1.)
		return (false);
	return (true);
}

bool	validate_line(char *line)
{
	char	*res;

	res = ft_strtrim(line, "ACLsplcy0123456789.,\t");
	if (res[0] == '\n')
		return (free(res), true);
	else
		return (free(res), false);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i])
			free(split[i++]);
		free(split);
	}
}

char	**split_and_check(char *input, char by, int fields, void *mem[3])
{
	char	**split;
	int		i;

	split = ft_split(input, by);
	if (!split)
	{
		free(mem[2]);
		free_split(mem[1]);
		ft_error(mem[0], "Invalid .rt file");
	}
	i = 0;
	while (i < fields)
		if (split[i])
			i += 1;
	else
		break ;
	if (split[i] || i < fields)
	{
		free(mem[2]);
		free_split(mem[1]);
		free_split(split);
		ft_error(mem[0], "Invalid .rt file");
	}
	return (split);
}

void	*obj(t_obj obj, t_list *lst)
{
	t_obj	*new;

	new = ft_calloc(sizeof(t_obj), 1);
	if (!new)
		ft_error(lst, "Memory allocation failed");
	return (ft_memcpy(new, &obj, sizeof(t_obj)));
}
