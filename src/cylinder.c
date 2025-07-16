#include "../include/minirt.h"

/*
 * this is for calculating the normal from a side hit
 */
inline static
t_vec3 point_s(const t_ray r,
    const float f[10],
    const t_vec3 ba,
    const t_vec3 oc)
{
    return (vec3_divide(vec3_subtract(vec3_add(oc, vec3_scale(r.dir, f[t])),
        vec3_divide(vec3_scale(ba, f[y]), f[baba])), f[ra]));
}

/*
 * and this for an end hit
 */
inline static
t_vec3 point(const t_vec3 ba, const float y, const float baba)
{
    return (vec3_divide(vec3_scale(ba, copysign(1., y)), sqrtf(baba)));
}

/*
 * x² + y² = r²
 * if this condition fills we do a tiny amount of math to
 * see whether we hit the side, or the end.
 */
t_intersection
intersect_cylinder(const t_ray r,
    const t_vec3 ba,
    const t_vec3 oc,
    const float rad)
{
	float	f[10];

	f[baba] = vec3_dot(ba, ba);
	f[bard] = vec3_dot(ba, r.dir);
	f[baoc] = vec3_dot(ba, oc);
	f[k2] = f[baba] - powf(f[bard], 2);
	f[k1] = f[baba] * vec3_dot(oc, r.dir) - f[baoc] * f[bard];
	f[k0] = f[baba] * vec3_dot(oc, oc) - powf(f[baoc], 2) - rad * rad * f[baba];
	f[h] = powf(f[k1], 2) - f[k2] * f[k0];
	if (f[h] < 0.0)
		return ((t_intersection){0});
	f[h] = sqrtf(f[h]);
	f[t] = (-f[k1] - f[h]) / f[k2];
	f[y] = f[baoc] + f[t] * f[bard];
	f[ra] = rad;
	if (f[y] > 0. && f[y] < f[baba])
		return ((t_intersection){f[t], CYL, point_s(r, f, ba, oc), {0}, NULL});
	if (f[y] < 0.)
		f[t] = -f[baoc] / f[bard];
	else
		f[t] = (f[baba] - f[baoc]) / f[bard];
	if (fabs(f[k1] + f[k2] * f[t]) < f[h])
		return ((t_intersection){f[t], CYL, point(ba, f[y], f[baba]), {0}, NULL});
	return ((t_intersection){0});
}

/*
 * we turn a center, orientation and diameter defined cylinder
 * into two extreme end points + radius defined one here.
 */
t_intersection	hit_cylinder(t_ray r, t_cylinder cy)
{
	const float		hh = cy.height * .5;
	const t_vec3	a = vec3_add(cy.pos, vec3_scale(cy.orientation, hh));
	const t_vec3	b = vec3_subtract(cy.pos, vec3_scale(cy.orientation, hh));
	const t_vec3	ba = vec3_subtract(b, a);
	const t_vec3	oc = vec3_subtract(r.origin, a);

	return (intersect_cylinder(r, ba, oc, cy.diameter / 2));
}

/*
 * this is for getting from the t and ray via at function the
 * surface normal of a cylinder hit
 */
t_vec3	cylinder_normal(t_vec3 p, t_vec3 a, t_vec3 b, float ra)
{
	const t_vec3	pa = vec3_subtract(p, a);
	const t_vec3	ba = vec3_subtract(b, a);
	const float		baba = vec3_dot(ba, ba);
	const float		paba = vec3_dot(pa, ba);
	const float		h = paba / baba;

	return (vec3_subtract(pa, vec3_divide(vec3_scale(ba, h), ra)));
}
