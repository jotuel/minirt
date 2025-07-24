#include  "../include/minirt.h"
#include <math.h>

/*
 * {\displaystyle \mathbf {v} _{\mathrm {rot} }=\mathbf {v} +(\sin \theta )(\mathbf {e} \times \mathbf {v} )+(1-\cos \theta )(\mathbf {e} \times (\mathbf {e} \times \mathbf {v} ))\,.}
 */
void rotate_cylinder(t_cylinder *cyl, bool dir, char axis)
{
	if (axis == 'x')
	{
		if (dir)
		{
			t_vec3 before = unit(subtract(cyl->orientation, cyl->pos));
			t_point cen = add(cyl->orientation, scale(before, cyl->height * .5f));
			t_vec3 after = unit(scale(before, M_PI_2));
			cyl->orientation = add(cen, scale(after, cyl->height * .5f));
			cyl->pos = subtract(cen, scale(after, cyl->height * .5f));
		}
	}
}

void rotate_x(t_map *map, bool dir)
{
		if (map->select->type)
			if (map->select->type == CYL)
				rotate_cylinder(&map->select->obj->cylinder, dir, 'x');

}

void rotate_y(t_map *map, bool dir)
{
	if (map->select->type)
		if (map->select->type == SPH)
			if (dir)
				;
}

void rotate_z(t_map *map, bool dir)
{
	if (map->select->type)
		if (map->select->type == SPH)
			if (dir)
				;
}
