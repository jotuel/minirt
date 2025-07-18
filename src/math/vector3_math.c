#include "../../include/minirt.h"

inline float	linear_to_gamma(float linear)
{
	if (linear > 0)
		return (sqrt(linear));
	return (0);
}

inline t_vec3	vec3_unit(t_vec3 v)
{
	return (vec3_scale(v, 1. / vec3_length(v)));
}

inline t_vec3	vec3_divide(t_vec3 vec, float scale)
{
	vec.x /= scale;
	vec.y /= scale;
	vec.z /= scale;
	return (vec);
}

// returns the point at the distance t along the ray
// position function
inline t_point	at(t_ray r, float t)
{
	return (vec3_add(r.origin, vec3_scale(r.dir, t)));
}
