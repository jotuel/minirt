#include "../../include/minirt.h"

static bool check_filetype(char *filename)
{
    char *ptr;

    ptr = ft_strchr(filename, '.');
    if (!ptr)
        return (false);
    if (!ft_strncmp(ptr, ".rt", 4))
        return (true);
    return (false);
}

static t_list *parse_line(char *line, t_list *lst)
{
    if (ft_strchr(line, 'L'))
        return (light(line, lst, (t_light){0}));
    else if (ft_strchr(line, 'C'))
        return (camera(line, lst, (t_camera){0}));
    else if (ft_strchr(line, 'A'))
        return (ambient(line, lst, (t_ambient){0}));
    else if (ft_strchr(line, 's'))
        return (sphere(line, lst, (t_sphere){0}));
    else if (ft_strchr(line, 'c'))
        return (cylinder(line, lst, (t_cylinder){0}));
    else if (ft_strchr(line, 'p'))
        return (plane(line, lst, (t_plane){0}));
    else
        return (false);
}

static t_list *file_parser(t_list *lst, int fd, char *line)
{
    while (line)
    {
        if (*line && line[0] != '\n')
            ft_lstadd_front(&lst, parse_line(line, lst));
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return lst;
}

t_list *parse_file(char *filename)
{
	t_list *lst;
	int		fd;

	lst = NULL;
    if (!filename || !check_filetype(filename))
    {
        ft_putendl_fd("Not a valid file", 2);
        return NULL;
    }
    fd = open(filename, O_RDONLY);
    if (-1 == fd)
        return NULL;
    lst = file_parser(lst, fd, ft_calloc(1, 1));
    return (lst);
}
