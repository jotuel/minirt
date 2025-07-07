#include "../include/minirt.h"

// intersect_sphere
t_cyl  hit_points_sphere(t_ray r, t_sphere sp)
{
	const t_vec3 oc = vec3_subtract(sp.pos, r.origin);
	const float a = powf(vec3_length(r.dir), 2);
	const float h = vec3_dot(r.dir, oc);
	const float c = powf(vec3_length(oc), 2) - powf(sp.diameter * .5f, 2);
	const float discrimant = powf(h, 2) - a * c;

	if (discrimant < 0)
		return ((t_cyl){.t1 = -1, .t0 = -1});
	return ((t_cyl){.t0 = (h - sqrtf(discrimant)) /  a, .t1 =(h + sqrtf(discrimant)) / a});
}

float hit_sphere(t_ray r, t_sphere sp)
{
	const t_cyl ts = hit_points_sphere(r, sp);

	if (ts.t0 < 0)
		return (-1.);
	else if (ts.t1 < 0)
		return (ts.t0);
	return (ts.t1);
}
