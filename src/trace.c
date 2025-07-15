#include "../include/minirt.h"
#include <stdint.h>

/*
 * we go through the cylinder, one by one, comparing the t values.
 * the smallest positive value found is returned with some additional
 * details about it.
 */
t_intersection intersect_cylinders(t_ray r, t_object *cy, const unsigned int nbr)
{
	t_intersection is;
	t_intersection tmp;
	unsigned int i;

	is = (t_intersection) { .type = NONE, .t = __FLT_MAX__ };
	i = 0;
	while (i < nbr)
	{
	    tmp = hit_cylinder(r, cy[i].cylinder);
		if (tmp.t > 0.0 && tmp.t < is.t)
		{
			is = tmp;
			is.type = CYLINDER;
			is.color = cy[i].cylinder.color;
			is.obj = &cy[i];
		}
		i += 1;
	}
	return (is);
}

/*
 * we go through the planes, one by one, comparing the t values.
 * the smallest positive value found is returned with some additional
 * details about it.
 */
t_intersection intersect_planes(t_ray r, t_object *pl, const unsigned int nbr)
{
    t_intersection is;
    t_intersection tmp;
    unsigned int i;

    is = (t_intersection) { .type = NONE, .t = __FLT_MAX__ };
    i = 0;
    while (i < nbr)
    {
        tmp = intersect_plane(r, pl[i].plane);
        if (tmp.t > 0.0 && tmp.t < is.t)
        	is = tmp;
        is.color = pl[i].plane.color;
        is.type = PLANE;
		is.obj = &pl[i];
        i += 1;
    }
    return (is);
}

/*
 * we go through the spheres, one by one, comparing the t values.
 * the smallest positive value found is returned with some additional
 * details about it.
 */
t_intersection intersect_spheres(t_ray r, t_object *sp, const unsigned int nbr)
{
	t_intersection is;
	t_intersection tmp;
	unsigned int i;

	tmp = (t_intersection) {0};
	is = (t_intersection) { .type = NONE, .t = __FLT_MAX__ };
	i = 0;
	while (i < nbr)
	{
	    tmp.t = hit_sphere(r, sp[i].sphere);
		if (tmp.t > 0.0 && tmp.t < is.t)
		{
			is = tmp;
			is.type = SPHERE;
			is.color = sp[i].sphere.color;
			is.obj = &sp[i];
		}
		i += 1;
	}
	return (is);
}

/*
 * calls all of the ray-object-intersect functions
 * then comparing the returned t values returning
 * the smallest positive out of all, if any exist.
 */
t_intersection intersections(t_ray r, t_map *map)
{
	t_intersection is;
	t_intersection tmp;
	float  tmin;

	tmin = __FLT_MAX__;
	is = (t_intersection) { .type = NONE };
	tmp = intersect_planes(r, map->pl, map->nbr_pl);
	if (tmp.t > 0.0 && tmp.t < tmin)
	{
		tmin = tmp.t;
		is = tmp;
	}
	tmp = intersect_spheres(r, map->sp, map->nbr_sp);
	if (tmp.t > 0.0 && tmp.t < tmin)
	{
		tmin = tmp.t;
		is = tmp;
	}
	tmp = intersect_cylinders(r, map->cy, map->nbr_cy);
	if (tmp.t > 0.0 && tmp.t < tmin)
	{
		tmin = tmp.t;
		is = tmp;
	}
	return (is);
}

// // this works but it doesnt take account what is the closest ray hit so that is
// // why it only renders one object at time
// uint_fast32_t color_ray(t_ray r, t_map *map)
// {
// 	// float		   a;
// 	// t_vec3		   unit_dir;
// 	t_intersection hit;
// 	t_ray	light;
// 	float	t;

// 	hit = intersections(r, map);
// 	return (get_color(hit.color));

// 	// else // only gradient background
// 	// {
// 	// 	a = 0.5 * (vec3_unit(r.dir).y + 1.0);
// 	// 	unit_dir = (vec3_add(vec3_scale((t_vec3) {1., 1., 1}, 1. - a), vec3_scale((t_vec3) {0.5, 0.7, 1.}, a)));
// 	// 	unit_dir = vec3_scale(unit_dir, 255);
// 	// 	return (get_color((t_color) {unit_dir.x, unit_dir.y, unit_dir.z}));
// 	// }
// }
