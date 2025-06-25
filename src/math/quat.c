#include "../../include/minirt.h"

t_quat quaternion_from_axis(t_vec3 from, t_vec3 to)
{
	const t_vec3 afrom = vec3_unit(from);
	const t_vec3 bto = vec3_unit(to);
	const float dot = vec3_dot(afrom, bto); // returns a scalar value of two vectors, the angle between them
	const t_vec3 axis = vec3_cross(afrom, bto); //gives me the axis to rotate from?
	const float angle = acosf(dot);
	float s;

	if (dot > 0.9999f) // no rotation needed
		return ((t_quat){{1, 0, 0}, 0});
	if (dot < -0.9999f) //the dot is -1 which means exactly the mirror rotation
	{// so the above cross production gives {0,0,0} so we find manually axis to rotate the cylinder
		t_vec3 orthogonal = vec3_cross(afrom, (t_vec3){1,0,0});
		if (vec3_length(orthogonal) < 0.0001f)
			orthogonal = vec3_cross(afrom, (t_vec3){0,0,1});
		orthogonal = vec3_unit(orthogonal);
		return ((t_quat){.w = 0, .v = {orthogonal.x, orthogonal.y, orthogonal.z}});
	}
	s = sinf(angle * 0.5f);
	return (quat_normalize((t_quat){.w = cosf(angle * 0.5f),
	.v.x = axis.x * s, .v.y = axis.y * s, .v.z = axis.z * s}));
}

t_vec3	rotate_vector_by_quaternion (t_vec3 v, t_quat q)
{
    return ((t_vec3)vec3_add(vec3_add(vec3_scale(q.v, vec3_dot(q.v, v) * 2.0f),
				vec3_scale(v, powf(q.w, 2) - vec3_dot(q.v, q.v))), vec3_scale(
				vec3_cross(q.v, v), 2.0f * q.w)));
}
