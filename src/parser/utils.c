#include "../../include/minirt.h"

void free_split(char **split)
{
	int i;

	i = 0;
	while(split[i])
		free(split[i++]);
	free(split);
}

char **split_and_check(char *input, char by, int fields, void *mem)
{
    char **split;
    int i;

    i = 0;
    split = ft_split(input, by);
    if (!split)
        ft_error(mem);
    while(split[i])
    	i++;
    if (i != fields)
    	ft_error(mem);
    return (split);
}
