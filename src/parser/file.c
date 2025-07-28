#include "../../include/minirt.h"
#include <stdlib.h>

static bool	check_filetype(char *filename)
{
	char	*ptr;

	ptr = ft_strchr(filename, '.');
	if (!ptr)
		return (false);
	if (!ft_strncmp(ptr, ".rt", 4))
		return (true);
	return (false);
}

static t_list	*parse_line(char *line, t_list *lst)
{
	if (!ft_strncmp(line, "L", 1))
		return (light(line, lst, (t_light){0}));
	else if (!ft_strncmp(line, "C", 1))
		return (camera(line, lst, (t_camera){0}));
	else if (!ft_strncmp(line, "A", 1))
		return (ambient(line, lst, (t_ambient){0}));
	else if (!ft_strncmp(line, "sp", 2))
		return (sphere(line, lst, (t_sphere){0}));
	else if (!ft_strncmp(line, "cy", 2))
		return (cylinder(line, lst, (t_cylinder){0}));
	else if (!ft_strncmp(line, "pl", 2))
		return (plane(line, lst, (t_plane){0}));
	else
		ft_error2(&lst, line, "Invalid line");
	return (lst);
}

static bool	trim_line(char *line)
{
	if (!line)
		return (false);
	while (*line)
	{
		if (ft_isspace(*line))
			*line = '\t';
		else if (ft_isalnum(*line) || *line == '.'
			|| *line == ',' || *line == '-')
			;
		else
			return (true);
		line++;
	}
	return (false);
}

static t_list	*file_parser(t_list *lst, FILE* fd, char *line)
{
	ssize_t nread;
	size_t len;

	while (	(nread = getline(&line, &len, fd)))
	{
		if (trim_line(line))
			ft_error(line, "Extra characters");
		if (*line && line[0] != '\t')
			ft_lstadd_front(&lst, parse_line(line, lst));
		free(line);
	}
	free(line);
	fclose(fd);
	return (lst);
}

t_list	*parse_file(char *filename)
{
	FILE*	fd;

	if (!filename || !check_filetype(filename))
	{
		ft_putendl_fd("Error\nInvalid filename", 2);
		exit(EXIT_FAILURE);
	}
	fd = fopen("scenes/scene.rt", "rb");
	if (!fd)
	{
		ft_putendl_fd("Error\nNot a valid file", 2);
		exit(EXIT_FAILURE);
	}
	return (file_parser(ft_lstnew(NULL), fd, ft_calloc(1, 1)));
}
