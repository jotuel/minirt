#include "../include/minirt.h"
#include <math.h>

// intersect_sphere
t_cyl  hit_points_sphere(t_ray r, t_sphere sp)
{
	const t_vec3 oc = vec3_subtract(r.origin, sp.pos);
	const float a = vec3_dot(oc, r.dir);
	//const float a = powf(vec3_length(r.dir), 2);
	// const float c = powf(vec3_length(oc), 2) - powf(sp.diameter * .5f, 2);
	const float c = vec3_dot(oc, oc) - powf(sp.diameter * .5f, 2);
	float h;
	//const float discrimant = powf(h, 2) - a * c;
	h = a*a - c;
	if (h < 0)
		return ((t_cyl){.t1 = -1, .t0 = -1});
	h = sqrtf(h);
	return ((t_cyl){.t0 = (-a - h), .t1 = -a + h});
}

float hit_sphere(t_ray r, t_sphere sp)
{
	const t_cyl ts = hit_points_sphere(r, sp);

	if (ts.t1 < 0)
		return (-1.);
	else if (ts.t0 < 0)
		return (ts.t1);
	return (ts.t0);
}
