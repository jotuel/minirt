#include "../../include/minirt.h"

inline t_vec3	neg(t_vec3 vec)
{
	return (subtract((t_vec3){0, 0, 0}, vec));
}

inline float	dot(t_vec3 v, t_vec3 w)
{
	return (v.x * w.x + v.y * w.y + v.z * w.z);
}

inline float	length(t_vec3 vec)
{
	return (sqrtf(dot(vec, vec)));
}

inline t_vec3	scale(t_vec3 vec, float scale)
{
	vec.x *= scale;
	vec.y *= scale;
	vec.z *= scale;
	return (vec);
}

inline t_vec3	cross(t_vec3 v, t_vec3 w)
{
	return ((t_vec3){.x = v.y * w.z - v.z * w.y, .y = v.z * w.x - v.x * w.z,
		.z = v.x * w.y - v.y * w.x});
}
