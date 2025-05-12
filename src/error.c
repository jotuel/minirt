#include "../include/minirt.h"

void ft_error(void *mem)
{
    perror("minirt");
    free(mem);
}
