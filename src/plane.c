#include "../include/minirt.h"
#include <math.h>

/*
 * Ax + By + Cz + D = 0
 * if this equation is satisfied the ray intersects the plane
 * checks first if the ray only hits very near infinity
 */
t_intersection intersect_plane(t_ray r, t_plane pl)
{
	float denom;
	float t;

	denom = vec3_dot(pl.orientation, r.dir);
	if (fabsf(denom) > 1e-4)
	{
		t = (vec3_dot(vec3_subtract(pl.pos, r.origin), pl.orientation) / denom);
		if (t > 1e-4)
			return ((t_intersection){.t = t,});
	}
	return ((t_intersection){0});
}
