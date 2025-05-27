#include "../../include/minirt.h"

void vec3_set_x(t_vec3 *vec, float x)
{
    vec->x = x;
}

void vec3_set_y(t_vec3 *vec, float y)
{
    vec->y = y;
}

void vec3_set_z(t_vec3 *vec, float z)
{
    vec->z = z;
}

float vec3_get_x(t_vec3 vec)
{
    return (vec.x);
}

float vec3_get_y(t_vec3 vec)
{
    return (vec.y);
}
