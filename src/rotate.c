/* ************************************************************************** */
/*                                                                            */
/*                                                     __     h  _ _  _| _    */
/*   rotate.c                                       __/ \\__  i (_(_)(_|(/_   */
/*                                                // \\__/ \\ v  _ _|_        */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>      \\__/ \\__/ e _>(_| | --    */
/*                                                // \\__/ \\ .  _  _ |       */
/*   Created: 2025/07/30 18:55:05 by ehaanpaa     \\__/ \\__/ f (_)(_)|       */
/*   Updated: 2025/07/30 18:55:05 by ehaanpaa        \\__/    i               */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	rotate_cylinder(t_cylinder *cyl, bool dir, char axis)
{
	t_point	center;
	float	angle;
	t_vec3	before;
	t_vec3	after;

	angle = 10 * (M_PI / 180);
	if (dir)
		angle = -angle;
	center = scale(add(cyl->pos, cyl->orientation), 0.5f);
	before = subtract(cyl->pos, center);
	after = (t_vec3){0};
	if (axis == 'x')
		after = (t_vec3){before.x,
			before.y * cosf(angle) - before.z * sinf(angle),
			before.y * sinf(angle) + before.z * cosf(angle)};
	else if (axis == 'y')
		after = (t_vec3){before.x * cosf(angle) + before.z * sinf(angle),
			before.y,
			before.x * -sinf(angle) + before.z * cosf(angle)};
	else if (axis == 'z')
		after = (t_vec3){before.x * cosf(angle) - before.y * sinf(angle),
			before.x * sinf(angle) + before.y * cosf(angle), before.z};
	cyl->pos = add(after, center);
	cyl->orientation = subtract(center, after);
}

void	rotate_x(t_map *map, bool dir)
{
	if (map->select->type)
		if (map->select->type == CYL)
			rotate_cylinder(&map->select->obj->cylinder, dir, 'x');
}

void	rotate_y(t_map *map, bool dir)
{
	if (map->select->type)
		if (map->select->type == CYL)
			rotate_cylinder(&map->select->obj->cylinder, dir, 'y');
}

void	rotate_z(t_map *map, bool dir)
{
	if (map->select->type)
		if (map->select->type == CYL)
			rotate_cylinder(&map->select->obj->cylinder, dir, 'z');
}
