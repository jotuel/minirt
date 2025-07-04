#include "../../include/minirt.h"

inline t_vec3	vec3_neg(t_vec3 vec)
{
	return (vec3_subtract((t_vec3){0, 0, 0}, vec));
}

inline float	vec3_dot(t_vec3 v, t_vec3 w)
{
	return (v.x * w.x + v.y * w.y + v.z * w.z);
}

inline float	vec3_length(t_vec3 vec)
{
	return (sqrtf(vec3_dot(vec, vec)));
}

inline t_vec3	vec3_scale(t_vec3 vec, float scale)
{
	vec.x *= scale;
	vec.y *= scale;
	vec.z *= scale;
	return (vec);
}

inline t_vec3	vec3_cross(t_vec3 v, t_vec3 w)
{
	return ((t_vec3){.x = v.y * w.z - v.z * w.y, .y = v.z * w.x - v.x * w.z,
		.z = v.x * w.y - v.y * w.x});
}
