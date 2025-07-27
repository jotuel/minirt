#include "../include/minirt.h"
#include <stdint.h>

/*
 * we go through the cylinder, one by one, comparing the t values.
 * the smallest positive value found is returned with some additional
 * details about it.
 */
t_isect	intersect_cylinders(t_ray r, t_object *cy,
		const unsigned int nbr)
{
	t_isect			is;
	t_isect			tmp;
	unsigned int	i;

	is = (t_isect){.type = NONE, .t = __FLT_MAX__};
	i = 0;
	while (i < nbr)
	{
		tmp = hit_cylinder(r, cy[i].cylinder);
		if (tmp.t > 0.0 && tmp.t < is.t)
		{
			is = tmp;
			is.type = CYL;
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
t_isect	intersect_planes(t_ray r, t_object *pl, const unsigned int nbr)
{
	t_isect			is;
	t_isect			tmp;
	unsigned int	i;

	is = (t_isect){.type = NONE, .t = __FLT_MAX__};
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
t_isect	intersect_spheres(t_ray r, t_object *sp, const unsigned int nbr)
{
	t_isect			is;
	t_isect			tmp;
	unsigned int	i;

	tmp = (t_isect){0};
	is = (t_isect){.type = NONE, .t = __FLT_MAX__};
	i = 0;
	while (i < nbr)
	{
		tmp.t = hit_sphere(r, sp[i].sphere);
		if (tmp.t > 0.0 && tmp.t < is.t)
		{
			is = tmp;
			is.type = SPH;
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
t_isect	intersections(t_ray r, t_map *map)
{
	t_isect			is;
	t_isect			tmp;
	float			tmin;

	tmin = __FLT_MAX__;
	is = (t_isect){0};
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
		return (tmp);
	return (is);
}

void	cast_rays(t_map *map)
{
	unsigned int	w;
	unsigned int	h;
	t_vec3			p_cen;
	t_ray			ray;

	initialize_camera(map->camera, map->img);
	w = 0;
	h = 0;
	while (w < map->img->width)
	#pragma omp parallel num_threads(5)
	{
		while (h < map->img->height)
		{
			p_cen = add(add(map->camera->p00,
						scale(map->camera->pixel_delta_u, h)),
					scale(map->camera->pixel_delta_v, w));
			ray = (t_ray){.origin = map->camera->lookfrom,
				.dir = unit(subtract(p_cen, map->camera->lookfrom))};
			mlx_put_pixel(map->img, w, h, color_ray(ray, map));
			#pragma omp atomic update
			h++;
		}
		#pragma omp atomic write
		h = 0;
		#pragma omp atomic update
		w++;
	}
}
