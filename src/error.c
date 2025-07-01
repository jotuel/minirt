#include "../include/minirt.h"
#include <stdio.h>
#include <stdlib.h>

void ft_error(void *mem)
{
	t_list *lst;

	lst = mem;
	stdout = stderr;
	printf("Error\nDanger, Will Robinson\n");
    ft_lstclear(&lst, free);
    exit(EXIT_FAILURE);
}
