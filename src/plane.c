/* ************************************************************************** */
/*                                                                            */
/*                                                     __     h  _ _  _| _    */
/*   plane.c                                        __/ \\__  i (_(_)(_|(/_   */
/*                                                // \\__/ \\ v  _ _|_        */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>      \\__/ \\__/ e _>(_| | --    */
/*                                                // \\__/ \\ .  _  _ |       */
/*   Created: 2025/07/30 18:56:29 by ehaanpaa     \\__/ \\__/ f (_)(_)|       */
/*   Updated: 2025/07/30 18:56:29 by ehaanpaa        \\__/    i               */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"
#include <math.h>

/*
 * Ax + By + Cz + D = 0
 * if this equation is satisfied the ray intersects the plane
 * checks first if the ray only hits very near infinity
 */
t_isect	intersect_plane(t_ray r, t_plane pl)
{
	float	denom;
	float	t;

	denom = dot(pl.orientation, r.dir);
	if (fabsf(denom) > 1e-4)
	{
		t = (dot(subtract(pl.pos, r.origin), pl.orientation) / denom);
		if (t > 1e-4)
			return ((t_isect){.t = t});
	}
	return ((t_isect){0});
}
