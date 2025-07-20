#include "../../include/minirt.h"

void	set_x(t_vec3 *vec, float x)
{
	vec->x = x;
}

void	set_y(t_vec3 *vec, float y)
{
	vec->y = y;
}

void	set_z(t_vec3 *vec, float z)
{
	vec->z = z;
}

float	get_x(t_vec3 vec)
{
	return (vec.x);
}

float	get_y(t_vec3 vec)
{
	return (vec.y);
}
