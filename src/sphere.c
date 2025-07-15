#include "../include/minirt.h"
#include <math.h>

/*
 * x² + y² + z² = r²
 * if this equation is satisfied the ray either
 * enters or exits the sphere. or both, could be both.
 */
t_cyl  hit_points_sphere(t_ray r, t_sphere sp)
{
	const t_vec3 oc = vec3_subtract(r.origin, sp.pos);
	const float a = vec3_dot(oc, r.dir);
	const float c = vec3_dot(oc, oc) - powf(sp.diameter * .5f, 2);
	float h;

	h = a*a - c;
	if (h < 0)
		return ((t_cyl){-1, -1});
	h = sqrtf(h);
	return ((t_cyl){.t0 = (-a - h), .t1 = -a + h});
}

/*
 * this finds the relevant t value to return and returns it.
 */
float hit_sphere(t_ray r, t_sphere sp)
{
	const t_cyl ts = hit_points_sphere(r, sp);

	if (ts.t1 < 0)
		return (-1.);
	else if (ts.t0 < 0)
		return (ts.t1);
	return (ts.t0);
}
