#include "../include/minirt.h"

t_color	color_scale(t_color vec, float scale)
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

static t_vec3 normal_at(t_ray r, t_intersection hit)
{
	t_vec3 v;

	v = (t_vec3){0,0,0};
	if (hit.type == SPHERE)
		v = vec3_unit(vec3_divide(vec3_subtract(at(r, hit.t), hit.obj->sphere.pos),
			hit.obj->sphere.diameter * .5));
	if (hit.type == PLANE)
		v = vec3_unit(vec3_cross(hit.obj->plane.orientation, r.dir));
	if (hit.type == CYLINDER)
		v = vec3_unit(hit.point);
	return (v);
}

// Check if the ray hits the light source, or is something blocking the light
static bool hit_light(t_ray r, float t, t_map *map)
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

static t_color phong_material(t_ray r, t_intersection hit, t_map *map)
{
	t_vec3	l_dir;
	t_vec3	n;
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;

	l_dir = vec3_subtract(map->light->pos, hit.point);
	ambient = ambient_color(hit, map);
	if (!hit_light((t_ray){hit.point, vec3_unit(l_dir)}, vec3_length(l_dir), map))
		return (ambient);
	specular = (t_color){0};
	n = normal_at(r, hit);
	l_dir = vec3_unit(l_dir);
	diffuse = diffuse_color(hit, map, l_dir, n);
	specular = specular_color(r, map, l_dir, n);
	return (add_colors(add_colors(diffuse, ambient), specular));
}

uint_fast32_t color_ray(t_ray r, t_map *map)
{
	// float		   a;
	// t_vec3		   unit_dir;
	t_intersection hit;

	hit = intersections(r, map);
	if (hit.type != NONE)
		return(get_color(phong_material(r, hit, map)));
	return (get_color((t_color){25,25,25}));

	// else // only gradient background
	// {
	// 	a = 0.5 * (vec3_unit(r.dir).y + 1.0);
	// 	unit_dir = (vec3_add(vec3_scale((t_vec3) {1., 1., 1}, 1. - a), vec3_scale((t_vec3) {0.5, 0.7, 1.}, a)));
	// 	unit_dir = vec3_scale(unit_dir, 255);
	// 	return (get_color((t_color) {unit_dir.x, unit_dir.y, unit_dir.z}));
	// }
}
