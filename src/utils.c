#include "../include/minirt.h"

void	*object_realloc(void *ptr, void *data, int nbr)
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
		ft_memcpy(new_ptr, data, sizeof(t_object));
	return (new_ptr);
}

void	*single_object(t_obj *data, t_type type, void *obj)
{
	if (type == AMB)
	{
		obj = ft_calloc(1, sizeof(t_ambient));
		if (!obj)
			return (NULL);
		return (ft_memcpy(obj, &data->ambiance, sizeof(t_ambient)));
	}
	else if (type == CAM)
	{
		obj = ft_calloc(1, sizeof(t_camera));
		if (!obj)
			return (NULL);
		return (ft_memcpy(obj, &data->cam, sizeof(t_camera)));
	}
	else if (type == LIGHT)
	{
		obj = ft_calloc(1, sizeof(t_light));
		if (!obj)
			return (NULL);
		return (ft_memcpy(obj, &data->light, sizeof(t_light)));
	}
	return (NULL);
}

void	*move_to_structs(t_obj *obj)
{
	static t_map	*map;

	if (!map)
		map = ft_calloc(1, sizeof(t_map));
	if (!obj || !map)
		return (NULL);
	else if (obj->type == AMB)
		map->ambient = single_object(obj, AMB, NULL);
	else if (obj->type == CAM)
		map->camera = single_object(obj, CAM, NULL);
	else if (obj->type == LIGHT)
		map->light = single_object(obj, LIGHT, NULL);
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

bool	has_alphabet(char *line)
{
	while (*line)
		if (ft_isalpha(*line++))
			return (true);
	return (false);
}
