#include "../include/minirt.h"

float color_plane(t_ray r)
{
	float	t;

	t = intersect_plane((t_vec3){0,0,-3.0}, (t_vec3){0,0,1}, r);
	if (t > 0.0)
		return (t);
	return (0);
}

float intersect_plane(t_vec3 center, t_vec3 rot, t_ray r)
{
	t_vec3 p0l0;
	float t;
	float denom;

	denom = vec3_dot(center, r.origin);
	if (denom >  1e-6)
		{
			p0l0 = vec3_subtract(rot, r.dir);
			t = vec3_dot(p0l0, center) / denom;
			printf("t:%f\n", t);
			return (t);
		}
	return (-1);
}
