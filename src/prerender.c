#include "../include/minirt.h"

void	convert_cylinders(t_map *map)
{
	float			h;
	t_vec3			hh;
	unsigned int	i;

	i = 0;
	while (i < map->nbr_cy)
	{
		h = map->cy[i].cylinder.height * .5f;
		hh = scale(map->cy[i].cylinder.orientation, h);
		map->cy[i].cylinder.orientation = add(map->cy[i].cylinder.pos, hh);
		map->cy[i].cylinder.pos = subtract(map->cy[i].cylinder.pos, hh);
		map->cy[i].cylinder.radius *= .5f;
		i += 1;
	}
}

void	convert_spheres(t_map *map)
{
	unsigned int	i;

	i = 0;
	while (i < map->nbr_sp)
	{
		map->sp[i].sphere.radius *= .5f;
		i += 1;
	}
}

void	convert_camera(t_camera *cam)
{
	if (cam->lookat.x == 0 && 1 == fabsf(cam->lookat.y) && cam->lookat.z == 0)
		cam->vup = (t_vec3){1, 0, 0};
	else
		cam->vup = (t_vec3){0, 1, 0};
}
