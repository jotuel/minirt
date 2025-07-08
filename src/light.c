#include "../include/minirt.h"
#include <math.h>

t_intersection intersect_cylinders(t_ray r, t_object *cy, const unsigned int nbr);
t_intersection intersect_planes(t_ray r, t_object *pl, const unsigned int nbr);
t_intersection intersect_spheres(t_ray r, t_object *sp, const unsigned int nbr);
t_color clamp_color(t_color a, t_color b);
t_color	add_colors(t_color color1, t_color color2);

inline static t_color	color_scale(t_color vec, float scale)
{
	int	r;
	int	g;
	int	b;

	if (scale == 1.)
		return (vec);
	r = fmin((int)vec.r * scale, 255);
	g = fmin((int)vec.g * scale, 255);
	b = fmin((int)vec.b * scale, 255);
	return ((t_color){r,g,b});
}

// does the ray hit light or is there object in between the light and object?
bool hit_light(t_ray r, float t, t_map *map)
{
	float	tt;

	r.origin = vec3_add(r.origin, vec3_scale(r.dir, 9e-3));
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

t_vec3 reflect(t_vec3 in, t_vec3 normal)
{
	return (vec3_subtract(in, vec3_scale(vec3_scale(normal, 2), vec3_dot(in, normal))));
}

t_vec3 normal_at(t_ray r, t_intersection hit)
{
	t_vec3 v;

	v = (t_vec3){0,0,0};
	if (hit.type == SPHERE)
		v = vec3_unit(vec3_divide(vec3_subtract(at(r, hit.t), hit.obj->sphere.pos), hit.obj->sphere.diameter * .5));
	if (hit.type == PLANE)
		v = vec3_unit(vec3_cross(hit.obj->plane.orientation, r.dir));
	if (hit.type == CYLINDER)
		v = vec3_unit(hit.point);
	return (v);
}


/// mix color = color1 + color2 / 2
// add_color = color1 + color2
// instead of mix color they must be added together and those values must be clamped. if over 255 then it is 255 and if under 0 then zero
/// possibly with floats
t_color lambertian_color(t_ray r, t_intersection hit, t_map *map)
{
	t_vec3	l_dir;
	t_ray	l_r;
	t_vec3	n;
	//t_vec3	re;
	t_color ambient;
	t_color diffuse;
	t_color effective_color;
	float light_dot_normal;
	float	t;

	l_dir = vec3_unit(vec3_subtract(map->light->pos, hit.point));
	l_r = (t_ray){hit.point, l_dir};
	t = vec3_length(l_dir);
	if (!hit_light(l_r, t, map)) //something is on the way and chasts a shadow
	{
		ambient = color_scale(clamp_color(map->ambient->color, hit.color), map->ambient->intensity);
		return (ambient);
	}
	// also add ambient color, multiply both of the colors by ambient intensity and then combine them
	n = normal_at(r, hit);
	//re = reflect(l_dir, n);
	// doesnt take accout light color <- mistake
	// color needs to be clamped to the min color value either by the light source or the obj color

	effective_color = color_scale(clamp_color(hit.color, map->light->color), map->light->intensity);
	ambient = color_scale(clamp_color(map->ambient->color, hit.color), map->ambient->intensity);
	light_dot_normal = vec3_dot(l_dir, n);
	// if (hit.type == CYLINDER)
	// 	light_dot_normal = fabs(light_dot_normal);
	if (light_dot_normal < 0)
		diffuse = (t_color){0};
	else
		diffuse = color_scale(color_scale(effective_color, 1), light_dot_normal);
	return (add_colors(diffuse, ambient));
}

// this works but it doesnt take account what is the closest ray hit so that is
// why it only renders one object at time
uint_fast32_t color_ray(t_ray r, t_map *map)
{
	// float		   a;
	// t_vec3		   unit_dir;
	t_intersection hit;

	hit = intersections(r, map);
	if (hit.type != NONE)
		return(get_color(lambertian_color(r, hit, map)));
	return (get_color((t_color){25,25,25}));

	// else // only gradient background
	// {
	// 	a = 0.5 * (vec3_unit(r.dir).y + 1.0);
	// 	unit_dir = (vec3_add(vec3_scale((t_vec3) {1., 1., 1}, 1. - a), vec3_scale((t_vec3) {0.5, 0.7, 1.}, a)));
	// 	unit_dir = vec3_scale(unit_dir, 255);
	// 	return (get_color((t_color) {unit_dir.x, unit_dir.y, unit_dir.z}));
	// }
}
