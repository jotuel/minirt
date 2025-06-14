#include "../include/minirt.h"

float vec3_dot(t_vec3 v, t_vec3 w)
{
	return (v.x * w.x + v.y * w.y + v.z * w.z);
}

float vec3_length(t_vec3 vec)
{
	return (sqrtf(vec3_dot(vec, vec)));
}

t_vec3	vec3_divide(t_vec3 vec, float scale)
{
	vec.x /= scale;
	vec.y /= scale;
	vec.z /= scale;
	return (vec);
}

t_vec3 vec3_scale(t_vec3 vec, float scale)
{
	vec.x *= scale;
	vec.y *= scale;
	vec.z *= scale;
	return (vec);
}

t_vec3 vec3_cross(t_vec3 v, t_vec3 w)
{
	return ((t_vec3)
		{.x = vec3_get_y(v) * vec3_get_z(w) - vec3_get_z(v) * vec3_get_y(w),
		.y = vec3_get_z(v) * vec3_get_x(w) - vec3_get_x(v) * vec3_get_x(w),
		.z = vec3_get_x(v) * vec3_get_y(w) - vec3_get_x(w) * vec3_get_y(v) });
}
