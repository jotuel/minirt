#include "../include/minirt.h"

// intersect_sphere
float  hit_sphere(t_point center, float radius, t_ray r)
{
	t_vec3 oc;
	float a;
	float h;
	float c;
	float discrimant;

	oc = vec3_subtract(center, r.origin);
	a = vec3_length(r.dir);
	a *= a;
	h = vec3_dot(r.dir, oc);
	c = vec3_length(oc);
	c = c * c - radius * radius;
	discrimant =  h * h - a * c;
	if (discrimant < 0)
		return (-1.);
	return ((h - sqrtf(discrimant)) / a);
}
