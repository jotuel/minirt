
#include "../../include/minirt.h"

bool validate_orientation(t_vec3 orien)
{
    if (orien.x > 1. || orien.x < 0.)
        return (false);
    else if (orien.y > 1. || orien.y < 0.)
        return (false);
    else if (orien.z > 1. || orien.z < 0.)
        return (false);
    return (true);
}

bool validate_line(char *line)
{
    char *res;

    res = ft_strtrim(line, "ACLsplcy0123456789.,\t");
    if (res[0] == '\n')
        return (free(res), true);
    else
        return (free(res), false);
}

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

    split = ft_split(input, by);
    if (!split)
        ft_error(mem);
    if (split[fields])
        ft_error(mem);
    while(fields--)
    {
        if(!split[fields])
            ft_error(mem);
    }
    return (split);
}
