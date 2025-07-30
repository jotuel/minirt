/* ************************************************************************** */
/*                                                                            */
/*                                                     __     h  _ _  _| _    */
/*   vector3.c                                      __/ \\__  i (_(_)(_|(/_   */
/*                                                // \\__/ \\ v  _ _|_        */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>      \\__/ \\__/ e _>(_| | --    */
/*                                                // \\__/ \\ .  _  _ |       */
/*   Created: 2025/07/30 19:14:06 by ehaanpaa     \\__/ \\__/ f (_)(_)|       */
/*   Updated: 2025/07/30 19:14:06 by ehaanpaa        \\__/    i               */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

float	get_z(t_vec3 vec)
{
	return (vec.z);
}

inline t_vec3	add(t_vec3 vec, t_vec3 vec1)
{
	return ((t_vec3){.x = vec.x + vec1.x, .y = vec.y + vec1.y, .z = vec.z
		+ vec1.z});
}

inline t_vec3	subtract(t_vec3 vec, t_vec3 vec1)
{
	return ((t_vec3){.x = vec.x - vec1.x, .y = vec.y - vec1.y, .z = vec.z
		- vec1.z});
}

inline t_vec3	multiply(t_vec3 vec, t_vec3 vec1)
{
	return ((t_vec3){.x = vec.x * vec1.x, .y = vec.y * vec1.y, .z = vec.z
		* vec1.z});
}

inline t_vec3	square(t_vec3 vec)
{
	return (multiply(vec, vec));
}
