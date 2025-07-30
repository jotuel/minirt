/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:30:02 by jtuomi            #+#    #+#             */
/*   Updated: 2024/12/18 20:23:20 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	return (get_delim(fd, '\n'));
}

char	*get_delim(int fd, char dl)
{
	t_string	str;
	char		c;

	str.str = NULL;
	str.len = 0;
	str.capacity = 0;
	while (1)
	{
		c = ft_getc(fd);
		if (c == EOF)
			break ;
		if (-1 == ft_putc(&str, c))
			return (free(str.str), NULL);
		if (c == dl)
		{
			break ;
		}
	}
	if (str.len > 0)
	{
		ft_putc(&str, '\0');
	}
	return (str.str);
}

int	ft_getc(int fd)
{
	static char	buf[BUFFER_SIZE];
	static char	*bufp;
	static int	n = 0;

	if (n == 0)
	{
		n = read(fd, buf, sizeof buf);
		bufp = buf;
	}
	if (--n >= 0)
		return ((unsigned char)*bufp++);
	return (EOF);
}

int	ft_putc(t_string *str, char c)
{
	if (str->len + 1 >= str->capacity)
	{
		str->capacity += BUFFER_SIZE;
		if (!str->str)
		{
			str->str = malloc(str->capacity * sizeof(char) + sizeof(char));
			if (!str->str)
				return (EOF);
		}
		else
		{
			str->str = ft_realloc(str->str, str->capacity, str->len);
			if (!str->str)
				return (EOF);
		}
	}
	str->str[str->len] = c;
	str->len++;
	return (0);
}

void	*ft_realloc(void *ptr, size_t size, size_t old_size)
{
	void	*mem;

	mem = malloc(size);
	if (!mem)
		return (NULL);
	mem = ft_memmove(mem, ptr, old_size);
	free(ptr);
	return (mem);
}
