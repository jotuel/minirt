#include "../include/minirt.h"

t_intersection	intersect_cylinder(t_ray r, t_vec3 ba, t_vec3 oc, float ra)
{
	float	arr[9];

	arr[0] = vec3_dot(ba, ba);
	arr[1] = vec3_dot(ba, r.dir);
	arr[2] = vec3_dot(ba, oc);
	arr[3] = arr[0] - powf(arr[1], 2);
	arr[4] = arr[0] * vec3_dot(oc, r.dir) - arr[2] * arr[1];
	arr[5] = arr[0] * vec3_dot(oc, oc) - powf(arr[2], 2) - powf(ra, 2) * arr[0];
	arr[6] = powf(arr[4], 2) - arr[3] * arr[5];
	if (arr[6] < 0.0)
		return ((t_intersection){0});
	arr[6] = sqrtf(arr[6]);
	arr[7] = (-arr[4] - arr[6]) / arr[3];
	arr[8] = arr[2] + arr[7] * arr[1];
	if (arr[8] > 0. && arr[8] < arr[0])
		return ((t_intersection){CYLINDER, arr[8], .point = at(r, arr[7])});
	if (arr[8] < 0.)
		arr[7] = -arr[2] / arr[1];
	else
		arr[7] = (arr[0] - arr[2]) / arr[1];
	if (fabs(arr[4] + arr[3] * arr[7]) < arr[6])
		return ((t_intersection){CYLINDER, arr[7], .point = at(r, arr[7])});
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
