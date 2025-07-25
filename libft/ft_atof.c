/* ************************************************************************** */
/*                                                                            */
/*                                                     __     h  _ _  _| _    */
/*   ft_atof.c                                      __/ \\__  i (_(_)(_|(/_   */
/*                                                // \\__/ \\ v  _ _|_        */
/*   By: jtuomi <jtuomi@student.hive.fi>          \\__/ \\__/ e _>(_| | --    */
/*                                                // \\__/ \\ .  _  _ |       */
/*   Created: 2025/07/16 12:06:41 by jtuomi       \\__/ \\__/ f (_)(_)|       */
/*   Updated: 2025/07/16 12:06:41 by jtuomi          \\__/    i               */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float ft_atof(const char *str)
{
    uint32_t	integer;
	uint32_t	fraction;
	size_t		power;
	float		sign;

	sign = 1.;
	if ((*str == '+' || *str == '-'))
		sign = 1. - 2 * (*str++ == '-');
	integer = 0;
	while ('0' <= *str && *str <= '9')
		integer = integer * 10 + *str++ - '0';
	if (*str == '.')
		++str;
	fraction = 0;
	power = 1;
	while ('0' <= *str && *str <= '9')
	{
		power *= 10;
		fraction = fraction * 10 + *str++ - '0';
	}
	return (sign * (integer + (float)fraction / power));
}
