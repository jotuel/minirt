#include "../include/minirt.h"

float vec3_get_z(t_vec3 vec)
{
    return (vec.z);
}

t_vec3 vec3_add(t_vec3 vec, t_vec3 vec1)
{
    return ((t_vec3){.x = vec.x + vec1.x,
        .y = vec.y + vec1.y,
        .z = vec.z + vec1.z});
}

t_vec3 vec3_subtract(t_vec3 vec, t_vec3 vec1)
{
    return ((t_vec3){.x = vec.x - vec1.x,
        .y = vec.y - vec1.y,
        .z = vec.z - vec1.z});
}

t_vec3 vec3_multiply(t_vec3 vec, t_vec3 vec1)
{
    return ((t_vec3){.x = vec.x * vec1.x,
        .y = vec.y * vec1.y,
        .z = vec.z * vec1.z});
}

t_vec3 vec3_square(t_vec3 vec)
{
    return (vec3_multiply(vec, vec));
}
