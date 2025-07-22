#include "../include/minirt.h"

/*
 * this is for calculating the normal from a side hit
 */
inline static t_vec3	point_s(const t_ray r, const float f[10],
		const t_vec3 ba, const t_vec3 oc)
{
	return (divide(subtract(add(oc, scale(r.dir, f[t])),
				divide(scale(ba, f[y]), f[baba])), f[ra]));
}

/*
 * and this for an end hit
 */
inline static t_vec3	point(const t_vec3 ba, const float y, const float baba)
{
	return (divide(scale(ba, copysign(1., y)), sqrtf(baba)));
}

/*
 * x² + y² = r²
 * if this condition fills we do a tiny amount of math to
 * see whether we hit the side, or the end.
 */
static
inline
t_isect	intersect_cylinder(const t_ray r, const t_vec3 ba,
		const t_vec3 oc, float *f)
{
	f[h] = sqrtf(f[h]);
	f[t] = (-f[k1] - f[h]) / f[k2];
	if (f[t] < 0.f || f[t] > (-f[k1] + f[h]) / f[k2])
		f[t] = (-f[k1] + f[h]) / f[k2];
	f[y] = f[baoc] + f[t] * f[bard];
	if (f[y] > 0. && f[y] < f[baba])
		return ((t_isect){f[t], CYL, point_s(r, f, ba, oc), {0}, NULL});
	if (f[y] < 0.)
		f[t] = -f[baoc] / f[bard];
	else
		f[t] = (f[baba] - f[baoc]) / f[bard];
	if (fabsf(f[k1] + f[k2] * f[t]) < f[h])
		return ((t_isect){f[t], CYL, point(ba, f[y], f[baba]), {0}, NULL});
	return ((t_isect){0});
}

/*
 * calculating whether ray hits the cylinder at all
 * before checking and returning where it hits
 */
t_isect	hit_cylinder(t_ray r, t_cylinder cy)
{
	const t_vec3	ba = subtract(cy.orientation, cy.pos);
	const t_vec3	oc = subtract(r.origin, cy.pos);
	float			f[10];

	f[ra] = cy.radius;
	f[baba] = dot(ba, ba);
	f[bard] = dot(ba, r.dir);
	f[baoc] = dot(ba, oc);
	f[k2] = f[baba] - f[bard] * f[bard];
	f[k1] = f[baba] * dot(oc, r.dir) - f[baoc] * f[bard];
	f[k0] = f[baba] * dot(oc, oc) - f[baoc] * f[baoc] - f[ra] * f[ra] * f[baba];
	f[h] = f[k1] * f[k1] - f[k2] * f[k0];
	if (f[h] < 0.0)
		return ((t_isect){0});
	return (intersect_cylinder(r, ba, oc, f));
}
