#include "../include/minirt.h"

// intersect_sphere
float  hit_sphere(t_sphere sp, t_ray r)
{
	const t_vec3 oc = vec3_subtract(sp.pos, r.origin);
	const float a = powf(vec3_length(r.dir), 2);
	const float h = vec3_dot(r.dir, oc);
	const float c = powf(vec3_length(oc), 2) - powf(sp.diameter * .5f, 2);
	const float discrimant = powf(h, 2) - a * c;

	if (discrimant < 0)
		return (-1.);
	return ((h - sqrtf(discrimant)) / a);
}
