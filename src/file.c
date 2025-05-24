#include "../include/minirt.h"

static bool check_filetype(char *filename)
{
    char *ptr;

    ptr = ft_strrchr(filename, '.');
    if (!ptr)
        return (false);
    if (ft_strncmp(ptr, ".rt", 4))
        return (true);
    return (false);
}

static bool parse_line(char *line, t_map *rt)
{
    if (ft_strchr(line, 'L'))
        return (light(line, rt, (t_light){0}), true);
    else if (ft_strchr(line, 'C'))
        return (camera(line, rt, (t_camera){0}), true);
    else if (ft_strchr(line, 'A'))
        return (ambient(line, rt, (t_ambient){0}), true);
    else if (ft_strchr(line, 's'))
        return (sphere(line, rt, (t_sphere){0}), true);
    else if (ft_strchr(line, 'c'))
        return (cylinder(line, rt, (t_cylinder){0}), true);
    else if (ft_strchr(line, 'p'))
        return (plane(line, rt, (t_plane){0}), true);
    else
        return (false);
}

static t_map file_parser(char *name, t_map minirt, int fd, char *line)
{
    fd = open(name, O_RDONLY);
    if (-1 == fd)
        return (minirt);
    line = ft_calloc(1, 1);
    while (line)
    {
        if (!line[0])
        {
            free(line);
            line = get_next_line(fd);
            continue ;
        }
        if (!parse_line(line, &minirt))
        {
            free(line);
            free(minirt.space);
            minirt.space = NULL;
            return (minirt);
        }
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (minirt);
}

t_map parse_file(char *filename, t_map minirt)
{
    if (!filename || !check_filetype(filename))
    {
        ft_putendl_fd("Not a valid file", 2);
        return (minirt);
    }
    minirt = file_parser(filename, minirt, 0, NULL);
    if (!minirt.space)
    {
        perror("malloc");
        return (minirt);
    }
    return (minirt);
}
