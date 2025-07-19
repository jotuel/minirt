#include "../include/minirt.h"

void *object_realloc(void *ptr, void *data, int nbr)
{
	t_object	*new_ptr;

	new_ptr = ft_calloc(nbr, sizeof(t_object));
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(new_ptr, ptr, sizeof(t_object) * (nbr - 1));
		ft_memcpy(&new_ptr[nbr - 1], data, sizeof(t_object));
		free(ptr);
	}
	else
	{
		ft_memcpy(new_ptr, data, sizeof(t_object));
	}
	return (new_ptr);
}

void	*move_to_structs(void *ptr)
{
	static t_map	*map;
	t_obj			*obj;

	if (!map)
	    map = ft_calloc(1, sizeof(t_map));
	obj = ptr;
	if (!obj)
		return (NULL);
	else if (obj->type == AMB)
		map->ambient = &obj->ambiance;
	else if (obj->type == CAM)
		map->camera = &obj->cam;
	else if (obj->type == LIGHT)
		map->light = &obj->light;
	else if (obj->type == PLANE)
		map->pl = object_realloc(map->pl, &obj->plane, ++map->nbr_pl);
	else if (obj->type == CYL)
		map->cy = object_realloc(map->cy, &obj->cylinder, ++map->nbr_cy);
	else
		map->sp = object_realloc(map->sp, &obj->sphere, ++map->nbr_sp);
	return (map);
}

void	brush(void *ptr)
{
	(void)ptr;
}
