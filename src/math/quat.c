#include "../../include/minirt.h"

inline t_quat	quaternion_from_axis(t_vec3 from, t_vec3 to)
{
	const t_vec3	afrom = vec3_unit(from);
	const t_vec3	bto = vec3_unit(to);
	const float		dot = vec3_dot(afrom, bto);
	const float		angle = acosf(dot);
	const t_vec3	axis = vec3_cross(afrom, bto);

	if (dot > 0.9999f)
		return ((t_quat){{1, 0, 0}, 0});
	if (dot < -0.9999f)
	{
		from = vec3_cross(afrom, (t_vec3){1, 0, 0});
		if (vec3_length(from) < 0.0001f)
			from = vec3_cross(afrom, (t_vec3){0, 0, 1});
		from = vec3_unit(from);
		return ((t_quat){.w = 0, .v = {from.x, from.y, from.z}});
	}
	return (quat_normalize((t_quat){.w = cosf(angle * 0.5f),
			.v = vec3_scale(axis, sinf(angle * .5f))}));
}

inline t_vec3	rotate_vector_by_quaternion(t_vec3 v, t_quat q)
{
	return ((t_vec3)vec3_add(vec3_add(vec3_scale(q.v, vec3_dot(q.v, v)
					* 2.0f), vec3_scale(v, powf(q.w, 2) - vec3_dot(q.v,
						q.v))), vec3_scale(vec3_cross(q.v, v), 2.0f
				* q.w)));
}

void	set_quaternion(float w, t_vec3 v, t_quat *q)
{
	q->w = w;
	q->v = v;
}

inline float	quat_norm(t_quat q)
{
	return (sqrtf(q.w * q.w + q.v.x * q.v.x + q.v.y * q.v.y + q.v.z * q.v.z));
}

inline t_quat	quat_normalize(t_quat q)
{
	const float	norm = quat_norm(q);

	if (norm == 0.0f)
		return ((t_quat){.w = 1.f, .v = (t_vec3){0.f, 0.f, 0.f}});
	return ((t_quat){.w = q.w / norm, .v = (t_vec3){q.v.x / norm, q.v.y / norm,
		q.v.z / norm}});
}
