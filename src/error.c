#include "../include/minirt.h"
#include <stdlib.h>

void	ft_error(void *mem)
{
	ft_putstr_fd("Error\n", 2);
	ft_lstclear((t_list **)&mem, free);
	exit(EXIT_FAILURE);
}
