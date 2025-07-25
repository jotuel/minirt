#include "../include/minirt.h"

void	translate_x(t_map *map, bool dir)
{
	if (map->select->type == SPH)
	{
		if (dir)
			map->select->obj->sphere.pos.x += 0.1;
		else
			map->select->obj->sphere.pos.x -= 0.1;
	}
	else if (map->select->type == CYL)
	{
		if (dir)
		{
			map->select->obj->cylinder.pos.x += 0.1;
			map->select->obj->cylinder.orientation.x += 0.1;
		}
		else
		{
			map->select->obj->cylinder.pos.x -= 0.1;
			map->select->obj->cylinder.orientation.x -= 0.1;
		}
	}
}

void	translate_y(t_map *map, bool dir)
{
	if (map->select->type)
	{
		if (map->select->type == SPH)
		{
			if (dir)
				map->select->obj->sphere.pos.y += 0.1;
			else
				map->select->obj->sphere.pos.y -= 0.1;
		}
		else if (map->select->type == CYL)
		{
			if (dir)
			{
				map->select->obj->cylinder.pos.y += 0.1;
				map->select->obj->cylinder.orientation.y += 0.1;
			}
			else
			{
				map->select->obj->cylinder.pos.y -= 0.1;
				map->select->obj->cylinder.orientation.y -= 0.1;
			}
		}
	}
}

void	translate_z(t_map *map, bool dir)
{
	if (map->select->type)
	{
		if (map->select->type == SPH)
		{
			if (dir)
				map->select->obj->sphere.pos.z += 0.1;
			else
				map->select->obj->sphere.pos.z -= 0.1;
		}
		else if (map->select->type == CYL)
		{
			if (dir)
			{
				map->select->obj->cylinder.pos.z += 0.1;
				map->select->obj->cylinder.orientation.z += 0.1;
			}
			else
			{
				map->select->obj->cylinder.pos.z -= 0.1;
				map->select->obj->cylinder.orientation.z -= 0.1;
			}
		}
	}
}
