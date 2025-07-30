/* ************************************************************************** */
/*                                                                            */
/*                                                     __     h  _ _  _| _    */
/*   vector.c                                       __/ \\__  i (_(_)(_|(/_   */
/*                                                // \\__/ \\ v  _ _|_        */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>      \\__/ \\__/ e _>(_| | --    */
/*                                                // \\__/ \\ .  _  _ |       */
/*   Created: 2025/07/30 19:14:22 by ehaanpaa     \\__/ \\__/ f (_)(_)|       */
/*   Updated: 2025/07/30 19:14:22 by ehaanpaa        \\__/    i               */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	set_x(t_vec3 *vec, float x)
{
	vec->x = x;
}

void	set_y(t_vec3 *vec, float y)
{
	vec->y = y;
}

void	set_z(t_vec3 *vec, float z)
{
	vec->z = z;
}

float	get_x(t_vec3 vec)
{
	return (vec.x);
}

float	get_y(t_vec3 vec)
{
	return (vec.y);
}
