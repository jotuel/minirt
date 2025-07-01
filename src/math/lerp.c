#include "../../include/types.h"
#include <stdint.h>

float	lerp(float s, float e, float f)
{
	return ((s * (1. - f)) + (e * f));
}

uint_fast8_t	color_lerp(float f)
{
	f = lerp(0., 1., f);
	return ((255 * f));
}

uint_fast32_t	vec3_lerp(t_vec3 v)
{
	return ((color_lerp(v.x) << 24) | (color_lerp(v.y) << 18) | (color_lerp(v.z) << 8) | 0xFF);
}
