/* ************************************************************************** */
/*                                                                            */
/*                                                     __     h  _ _  _| _    */
/*   error.c                                        __/ \\__  i (_(_)(_|(/_   */
/*                                                // \\__/ \\ v  _ _|_        */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>      \\__/ \\__/ e _>(_| | --    */
/*                                                // \\__/ \\ .  _  _ |       */
/*   Created: 2025/07/30 18:57:28 by ehaanpaa     \\__/ \\__/ f (_)(_)|       */
/*   Updated: 2025/07/30 18:57:28 by ehaanpaa        \\__/    i               */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"
#include <stdlib.h>

void	ft_error(void *mem, char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	ft_lstclear((t_list **)&mem, free);
	exit(EXIT_FAILURE);
}

void	ft_error1(t_map *map, char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	if (map)
	{
		free(map->ambient);
		free(map->camera);
		free(map->cy);
		free(map->light);
		free(map->pl);
		free(map->sp);
		free(map);
	}
	exit(EXIT_FAILURE);
}

void	ft_error2(t_list **lst, void *line, char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	free(line);
	ft_lstclear(lst, free);
	exit(EXIT_FAILURE);
}
