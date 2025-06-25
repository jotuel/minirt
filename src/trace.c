#include "../include/minirt.h"
#include <stdint.h>

// adding hittable objects to linkedlist with enum types and creating a function call
// that recognices which object was hit and goes to the right function
// it should remember the closest hit ray position and color that pos
t_intersection intersections(t_ray r, t_map *map)
{
	t_type type;
	float  t;
	float  tmin;

	tmin = __FLT_MAX__;
	type = NONE;
	t = hit_sphere(r, *map->sp);
	if (t > 0.0 && t < tmin)
	{
		tmin = t;
		type = SPHERE;
	}
	t = hit_cylinder(r, *map->cy);
	if (t > 0.0 && t < tmin)
	{
		tmin = t;
		type = CYLINDER;
	}
	t = color_plane(r, *map->pl);
	if (t > 0.0 && t < tmin)
	{
		tmin = t;
		type = PLANE;
	}
	return ((t_intersection) {.type = type, .t = tmin});
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
	{
		unit_dir = vec3_unit(vec3_subtract(at(r, hit.t), map->sp->pos));
		unit_dir = vec3_scale(vec3_add(unit_dir, (t_vec3) {1, 1, 1}), .5f);
		return (get_color((t_color) {unit_dir.x * 255, unit_dir.y * 255, unit_dir.z * 255}));
	}
	else if (hit.type == CYLINDER)
	{
		unit_dir = vec3_unit(vec3_subtract(
			at(r, hit.t), (t_vec3) {map->cy->pos.x, at(r, hit.t).y, map->cy->pos.z}));
		unit_dir = vec3_scale(vec3_add(unit_dir, (t_vec3) {1, 0, 1}), .5f);
		return (get_color((t_color) {unit_dir.x * 255, 0, unit_dir.z * 255}));
	}
	else if (hit.type == PLANE)
		return (-1);
	else // only gradient background
	{
		a = 0.5 * (vec3_unit(r.dir).y + 1.0);
		unit_dir = (vec3_add(vec3_scale((t_vec3) {1., 1., 1}, 1. - a), vec3_scale((t_vec3) {0.5, 0.7, 1.}, a)));
		unit_dir = vec3_scale(unit_dir, 255);
		return (get_color((t_color) {unit_dir.x, unit_dir.y, unit_dir.z}));
	}
}
