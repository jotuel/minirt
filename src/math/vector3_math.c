#include "../../include/minirt.h"

inline float	linear_to_gamma(float linear)
{
	if (linear > 0)
		return (sqrt(linear));
	return (0);
}

inline t_vec3	unit(t_vec3 v)
{
	return (scale(v, 1. / length(v)));
}

inline t_vec3	divide(t_vec3 vec, float scale)
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
	return (add(r.origin, scale(r.dir, t)));
}
