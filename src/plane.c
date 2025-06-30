#include "../include/minirt.h"

t_intersection intersect_plane(t_ray r, t_plane pl)
{
	float denom;
	float t;

	denom = vec3_dot(pl.orientation, r.dir);
	if (fabs(denom) > 1e-4)
	{
		t = (vec3_dot(vec3_subtract(pl.pos, r.origin), pl.orientation) / denom);
		if (t > 1e-4)
			return ((t_intersection){.t = t, .point = at(r, t)});
	}
	return ((t_intersection){0});
}
