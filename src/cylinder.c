#include "../include/minirt.h"

// inline static
// t_vec3 point_s(const t_ray r,
//     const float f[10],
//     const t_vec3 ba,
//     const t_vec3 oc)
// {
//     return (vec3_divide(vec3_subtract(vec3_add(oc, vec3_scale(r.dir, f[t])),
//         vec3_divide(vec3_scale(ba, f[y]), f[baba])), f[ra]));
// }

// inline static
// t_vec3 point(const t_vec3 ba, const float y, const float baba)
// {
//     return (vec3_divide(vec3_scale(ba, copysignf(1., y)), sqrtf(baba)));
// }

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
		return ((t_intersection){CYLINDER, f[t], .point = at(r, f[t])});
	if (f[y] < 0.)
		f[t] = -f[baoc] / f[bard];
	else
		f[t] = (f[baba] - f[baoc]) / f[bard];
	if (fabs(f[k1] + f[k2] * f[t]) < f[h])
		return ((t_intersection){CYLINDER, f[t], .point = at(r, f[t])});
	return ((t_intersection){0});
}

t_intersection	hit_cylinder(t_ray r, t_cylinder cy)
{
	const float		hh = cy.height * .5;
	const t_vec3	a = vec3_add(cy.pos, vec3_scale(cy.orientation, hh));
	const t_vec3	b = vec3_subtract(cy.pos, vec3_scale(cy.orientation, hh));
	const t_vec3	ba = vec3_subtract(b, a);
	const t_vec3	oc = vec3_subtract(r.origin, a);

	return (intersect_cylinder(r, ba, oc, cy.diameter / 2));
}

t_vec3	cylinder_normal(t_vec3 p, t_vec3 a, t_vec3 b, float ra)
{
	const t_vec3	pa = vec3_subtract(p, a);
	const t_vec3	ba = vec3_subtract(b, a);
	const float		baba = vec3_dot(ba, ba);
	const float		paba = vec3_dot(pa, ba);
	const float		h = paba / baba;

	return (vec3_subtract(pa, vec3_divide(vec3_scale(ba, h), ra)));
}
