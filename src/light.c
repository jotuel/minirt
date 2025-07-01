#include "../include/minirt.h"
#include <stdint.h>

t_intersection intersect_cylinders(t_ray r, t_object *cy, const unsigned int nbr);
t_intersection intersect_planes(t_ray r, t_object *pl, const unsigned int nbr);
t_intersection intersect_spheres(t_ray r, t_object *sp, const unsigned int nbr);

inline t_color	color_scale(t_color vec, float scale)
{
	vec.r *= scale;
	vec.g *= scale;
	vec.b *= scale;
	return (vec);
}

// creat intersections function for light that stops immeadately if finds t value that is smaller than
// the at(light) = t; <- this inversed math maybe this = vec3_lenght(vec3_subtract(hit.point, map->light->pos))
bool hit_light(t_ray r, float t, t_map *map)
{
	float	tt;

	r.origin = vec3_add(r.origin, vec3_scale(r.dir, 1e-4));
	tt = intersect_planes(r, map->pl, map->nbr_pl).t;
	if (tt < t && tt > 0.0f)
		return (false);
	tt = intersect_spheres(r, map->sp, map->nbr_sp).t;
	if (tt < t && tt > 0.0f)
		return (false);
	tt = intersect_cylinders(r, map->cy, map->nbr_cy).t;
	if (tt < t && tt > 0.0f)
		return (false);
	return (true);
}

// this works but it doesnt take account what is the closest ray hit so that is
// why it only renders one object at time
uint_fast32_t color_ray(t_ray r, t_map *map)
{
	// float		   a;
	// t_vec3		   unit_dir;
	t_intersection hit;
	t_ray	light;
	float	t;

	hit = intersections(r, map);
	light = (t_ray){hit.point, vec3_subtract(hit.point, map->light->pos)};
	t = vec3_length(vec3_subtract(hit.point, map->light->pos));
	if (!hit_light(light, t, map))
		return (get_color(color_scale(hit.color, map->ambient->intensity)));
	return (get_color(hit.color)); // with color

	// else // only gradient background
	// {
	// 	a = 0.5 * (vec3_unit(r.dir).y + 1.0);
	// 	unit_dir = (vec3_add(vec3_scale((t_vec3) {1., 1., 1}, 1. - a), vec3_scale((t_vec3) {0.5, 0.7, 1.}, a)));
	// 	unit_dir = vec3_scale(unit_dir, 255);
	// 	return (get_color((t_color) {unit_dir.x, unit_dir.y, unit_dir.z}));
	// }
}
