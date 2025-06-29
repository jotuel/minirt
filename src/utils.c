#include "../include/minirt.h"

void	*move_to_structs(void *ptr)
{
	static t_map	*map;
	t_obj			*obj;

	if (!map)
		map = ft_calloc(1, sizeof(t_map));
	obj = ptr;
	if (!obj)
		return (NULL);
	else if (obj->type == AMBIENT)
		map->ambient = &obj->ambiance;
	else if (obj->type == CAMERA)
		map->camera = &obj->cam;
	else if (obj->type == LIGHT)
		map->light = &obj->light;
	else if (obj->type == PLANE)
		map->pl = &obj->plane;
	else if (obj->type == CYLINDER)
		map->cy = &obj->cylinder;
	else
		map->sp = &obj->sphere;
	return (map);
}

void	brush(void *ptr)
{
	(void)ptr;
}
