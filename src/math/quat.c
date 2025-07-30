/* ************************************************************************** */
/*                                                                            */
/*                                                     __     h  _ _  _| _    */
/*   quat.c                                         __/ \\__  i (_(_)(_|(/_   */
/*                                                // \\__/ \\ v  _ _|_        */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>      \\__/ \\__/ e _>(_| | --    */
/*                                                // \\__/ \\ .  _  _ |       */
/*   Created: 2025/07/30 19:13:45 by ehaanpaa     \\__/ \\__/ f (_)(_)|       */
/*   Updated: 2025/07/30 19:13:45 by ehaanpaa        \\__/    i               */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

inline t_quat	quaternion_from_axis(t_vec3 from, t_vec3 to)
{
	const t_vec3	afrom = unit(from);
	const t_vec3	bto = unit(to);
	const float		ab = dot(afrom, bto);
	const float		angle = acosf(ab);
	const t_vec3	axis = cross(afrom, bto);

	if (ab > 0.9999f)
		return ((t_quat){{1, 0, 0}, 0});
	if (ab < -0.9999f)
	{
		from = cross(afrom, (t_vec3){1, 0, 0});
		if (length(from) < 0.0001f)
			from = cross(afrom, (t_vec3){0, 0, 1});
		from = unit(from);
		return ((t_quat){.w = 0, .v = {from.x, from.y, from.z}});
	}
	return (quat_normalize((t_quat){.w = cosf(angle * 0.5f),
			.v = scale(axis, sinf(angle * .5f))}));
}

inline t_vec3	rotate_vector_by_quaternion(t_vec3 v, t_quat q)
{
	return ((t_vec3)add(add(scale(q.v, dot(q.v, v)
					* 2.0f), scale(v, powf(q.w, 2) - dot(q.v,
						q.v))), scale(cross(q.v, v), 2.0f
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
