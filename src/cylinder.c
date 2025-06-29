#include "../include/minirt.h"

t_intersection intersect_cylinder(t_ray r, t_vec3 a, t_vec3 b, float ra)
{
	const t_vec3 ba = vec3_subtract(b, a);
	const t_vec3 oc = vec3_subtract(r.origin, a);
	const float  baba = vec3_dot(ba, ba);
	const float  bard = vec3_dot(ba, r.dir);
	const float  baoc = vec3_dot(ba, oc);
	const float  k2 = baba - powf(bard, 2);
	const float  k1 = baba * vec3_dot(oc, r.dir) - baoc * bard;
	const float k0 = baba * vec3_dot(oc, oc) - powf(baoc, 2) - powf(ra, 2) * baba;
	float h, t, y;

	h = powf(k1, 2) - k2 * k0;
	if (h < 0.0)
		return ((t_intersection) {0});
	h = sqrtf(h);
	t = (-k1 - h) / k2;
	y = baoc + t * bard;
	if (y > 0. && y < baba)
		return ((t_intersection) {CYLINDER, y, .point = at(r, t)});
	if (y < 0.)
		t = -baoc / bard;
	else
		t = (baba - baoc) / bard;
	if (fabs(k1 + k2 * t) < h)
		return ((t_intersection) {CYLINDER, y, .point = at(r, t)});
	return ((t_intersection) {0});
}

t_intersection hit_cylinder(t_ray r, t_cylinder cy)
{
	const float hh = cy.height * .5;

	return (intersect_cylinder(r, vec3_add(cy.pos, vec3_scale(cy.orientation, hh)), vec3_subtract(cy.pos, vec3_scale(cy.orientation, hh)), cy.diameter / 2));
}

t_vec3 cylinder_normal(t_vec3 p, t_vec3 a, t_vec3 b, float ra)
{
	const t_vec3 pa = vec3_subtract(p, a);
	const t_vec3 ba = vec3_subtract(b, a);
	const float  baba = vec3_dot(ba, ba);
	const float  paba = vec3_dot(pa, ba);
	const float  h = paba / baba;

	return (vec3_subtract(pa, vec3_divide(vec3_scale(ba, h), ra)));
}
