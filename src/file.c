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

static bool parse_line(char *line, t_list *lst)
{
    if (ft_strchr(line, 'L'))
        return (light(line, lst, (t_light){0}), true);
    else if (ft_strchr(line, 'C'))
        return (camera(line, lst, (t_camera){0}), true);
    else if (ft_strchr(line, 'A'))
        return (ambient(line, lst, (t_ambient){0}), true);
    else if (ft_strchr(line, 's'))
        return (sphere(line, lst, (t_sphere){0}), true);
    else if (ft_strchr(line, 'c'))
        return (cylinder(line, lst, (t_cylinder){0}), true);
    else if (ft_strchr(line, 'p'))
        return (plane(line, lst, (t_plane){0}), true);
    else
        return (false);
}

static t_list *file_parser(char *name, t_list *lst, int fd, char *line)
{
    fd = open(name, O_RDONLY);
    if (-1 == fd)
        return NULL;
    line = ft_calloc(1, 1);
    while (line)
    {
        if (!line[0])
        {
            free(line);
            line = get_next_line(fd);
            continue ;
        }
        if (!parse_line(line, lst))
        {
            free(line);
            ft_lstclear(&lst, free);
            return NULL;
        }
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return lst;
}

t_list *parse_file(char *filename)
{
	t_list *lst;

	lst = NULL;
    if (!filename || !check_filetype(filename))
    {
        ft_putendl_fd("Not a valid file", 2);
        return NULL;
    }
    lst = file_parser(filename, lst, 0, NULL);
    return (lst);
}
