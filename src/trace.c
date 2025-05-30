#include "../include/minirt.h"
#include <stdint.h>

static t_point at(t_ray r, float t)
{
	return (vec3_add(r.origin, vec3_scale(r.dir, t)));
}

static uint_fast32_t color_plane(t_ray r)
{
	if (intersect_plane((t_vec3){0,0,0.3}, (t_vec3){1,1,0}, r.origin, r.dir))
		return (INT_MAX);
	return (0);
}

uint_fast32_t color_ray(t_ray r)
{
	float t;
	float a;
	t_vec3 unit_dir;

	if (color_plane(r))
	 	return (color_plane(r));
	t = hit_sphere((t_point){0,0,-1}, .3, r);
	if (t > 0.0)
	{
		unit_dir = vec3_unit(vec3_subtract(at(r, t), (t_vec3){0,0,-1}));
		unit_dir = vec3_scale(vec3_add(unit_dir, (t_vec3){1,1,1}), .5f);
		return (get_color((t_color){unit_dir.x*255,unit_dir.y*255,unit_dir.z*255}));
	}
	a = 0.5*(vec3_unit(r.dir).y + 1.0);
	unit_dir = (vec3_add(vec3_scale((t_vec3){1.,1.,1}, 1.-a), vec3_scale((t_vec3){0.5,0.7,1.}, a)));
	unit_dir = vec3_scale(unit_dir, 255);
	return (get_color((t_color){unit_dir.x, unit_dir.y, unit_dir.z}));
}

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
