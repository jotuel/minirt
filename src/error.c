#include "../include/minirt.h"
#include <stdlib.h>

void ft_error(void *mem)
{
    perror("minirt");
    free(mem);
    exit(EXIT_FAILURE);
}
