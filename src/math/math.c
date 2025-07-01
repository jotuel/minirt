#include "../../include/minirt.h"

inline t_vec3	refraction(t_vec3 uv, t_vec3 n, float e)
{
	float	cos_theta;
	t_vec3	rout_perp;
	t_vec3	rout_para;

	cos_theta = fmin(vec3_dot(vec3_neg(uv), n), 1);
	rout_perp = vec3_scale(vec3_add(uv, vec3_scale(n, cos_theta)), e);
	rout_para = vec3_scale(n, -sqrtf(fabs(1.0 - vec3_dot(rout_perp,
						rout_perp))));
	return (vec3_add(rout_para, rout_perp));
}

inline float	reflectance(float cos, float idx)
{
	float	r0;

	r0 = (1.0 - idx) / (1.0 - idx);
	r0 *= r0;
	return (r0 + (1.0 - r0) * (pow(1.0 - cos, 5)));
}

inline t_vec3	reflection(t_vec3 vec, t_vec3 n)
{
	return (vec3_subtract(vec, vec3_scale(n, 2 * vec3_dot(vec, n))));
}

inline float	to_radians(float degrees)
{
	return (M_PI * degrees / 180.0);
}

inline float	to_degrees(float radians)
{
	return (radians * (180.0 / M_PI));
}
