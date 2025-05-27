#include "../include/minirt.h"

inline
float	degree_to_radians(float degrees)
{
	return (degrees * M_PI/180.0);
}

inline
float	radians_to_degrees(float radians)
{
	return (radians * 180.0/M_PI);
}