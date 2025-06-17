#include "../include/minirt.h"
#include <stdlib.h>

void ft_error(void *mem)
{
	t_list *lst;

	lst = mem;
    perror("minirt");
    ft_lstclear(&lst, free);
    exit(EXIT_FAILURE);
}
