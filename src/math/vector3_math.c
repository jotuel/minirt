#include "../../include/minirt.h"

void set_vec3(char **vec3, t_vec3 *vec)
{
	vec3_set_x(vec, ft_atof(vec3[0]));
	vec3_set_y(vec, ft_atof(vec3[1]));
	vec3_set_z(vec, ft_atof(vec3[2]));
}

inline float linear_to_gamma(float linear)
{
	if (linear > 0)
		return (sqrt(linear));
	return (0);
}

t_vec3 vec3_unit(t_vec3 v)
{
	return (vec3_scale(v, 1. / vec3_length(v)));
}

t_vec3 vec3_divide(t_vec3 vec, float scale)
{
	vec.x /= scale;
	vec.y /= scale;
	vec.z /= scale;
	return (vec);
}
