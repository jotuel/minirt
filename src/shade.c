#include "../include/minirt.h"

static inline t_color	clamp_color(t_color a, t_color b)
{
	t_color	color;

	color = a;
	if (a.r > b.r)
		color.r = b.r;
	if (a.g > b.g)
		color.g = b.g;
	if (a.b > b.b)
		color.b = b.b;
	return (color);
}

static t_vec3	reflect(t_vec3 in, t_vec3 normal)
{
	return (subtract(in, scale(scale(normal, 2), dot(in,
					normal))));
}

inline t_color	ambient_color(t_isect hit, t_map *map)
{
	return (color_scale(clamp_color(map->ambient->color, hit.color),
			map->ambient->intensity));
}

t_color	diffuse_color(t_isect hit, t_map *map, t_vec3 l_dir,
		t_vec3 normal)
{
	t_color	effective_color;
	t_color	diffuse;
	float	light_dot_normal;

	effective_color = color_scale(clamp_color(hit.color, map->light->color),
			map->light->intensity);
	light_dot_normal = dot(l_dir, normal);
	if (light_dot_normal < 0)
		diffuse = (t_color){0};
	else
		diffuse = color_scale(color_scale(effective_color, 1),
				light_dot_normal);
	return (diffuse);
}

t_color	specular_color(t_ray r, t_map *map, t_vec3 l_dir, t_vec3 normal)
{
	t_vec3 re;
	t_color specular;
	float re_dot_eye;
	float factor;

	specular = (t_color){255, 255, 255};
	re = reflect(l_dir, normal);
	re_dot_eye = dot(re, r.dir);
	if (re_dot_eye <= 0)
		specular = (t_color){0};
	else
	{
		factor = powf(re_dot_eye, 50.0);
		specular = color_scale(color_scale(color_scale(specular,
						map->light->intensity), 0.8), factor);
	}
	return (specular);
}
