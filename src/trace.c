#include "../include/minirt.h"
#include <stdint.h>

// adding hittable objects to linkedlist with enum types and creating a function call
// that recognices which object was hit and goes to the right function
// it should remember the closest hit ray position and color that pos
t_intersection intersections(t_ray r, t_map *map)
{
	t_intersection is;
	float  t;
	float  tmin;

	tmin = __FLT_MAX__;
	is.type = NONE;
	t = intersect_plane(r, *map->pl).t;
	if (t > 0.0 && t < tmin)
	{
		tmin = t;
		is.type = PLANE;
		is.t = t;
	}
	t = hit_sphere(r, *map->sp);
	if (t > 0.0 && t < tmin)
	{
		tmin = t;
		is.type = SPHERE;
		is.t = t;
	}
	t = hit_cylinder(r, *map->cy).t;
	if (t > 0.0 && t < tmin)
	{
		tmin = t;
		is.type = CYLINDER;
		is.t = t;
	}
	return (is);
}

// this works but it doesnt take account what is the closest ray hit so that is
// why it only renders one object at time
uint_fast32_t color_ray(t_ray r, t_map *map)
{
	float		   a;
	t_vec3		   unit_dir;
	t_intersection hit;

	hit = intersections(r, map);
	if (hit.type == SPHERE)
		return (get_color(map->sp->color));
	else if (hit.type == CYLINDER)
		return (get_color(map->cy->color));
	else if (hit.type == PLANE)
		return (get_color(map->pl->color));
	else // only gradient background
	{
		a = 0.5 * (vec3_unit(r.dir).y + 1.0);
		unit_dir = (vec3_add(vec3_scale((t_vec3) {1., 1., 1}, 1. - a), vec3_scale((t_vec3) {0.5, 0.7, 1.}, a)));
		unit_dir = vec3_scale(unit_dir, 255);
		return (get_color((t_color) {unit_dir.x, unit_dir.y, unit_dir.z}));
	}
}
