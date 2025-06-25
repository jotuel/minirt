#include "../include/minirt.h"

//create hit cylinder function
typedef struct s_cyl
{
	float	t0;
	float	t1;

}				t_cyl;

bool	check_cap(t_ray r, float t, t_cylinder cy)
{
	t_vec3 tmp;
	float dist;
	float phi;

	tmp = vec3_add(r.origin, vec3_scale(r.dir, t));
	tmp.z = 0;
	dist = vec3_dot(tmp, tmp);
	if (dist <= powf(cy.diameter / 2, 2))
		return false;
	phi = atan2(tmp.y, tmp.x);
	if (phi < 0)
		return false;
	return true;
}

//TODO: instead of returning t once, both need to be checked and returned
t_cyl	intersect_caps(t_ray r, t_cylinder cy)
{
	t_cyl 	ct;
	float	t;

	ct = (t_cyl){0};
	if (cy.closed == false || (r.dir.y <= 0.00001))
		return (ct);
	t = (cy.min - r.origin.z) / r.dir.z;
	if (check_cap(r, t, cy))
		ct.t0 = t;
	t = (cy.max - r.origin.z) / r.dir.z;
	if (check_cap(r, t, cy))
		ct.t1 = t;
	return (ct);
}




// cylinder pos and orientation
// float cy.diameter
// float cy.height
t_cyl intersect_cylinder(t_ray r, t_cylinder cy)
{
	const float	a = powf(r.dir.x, 2) + powf(r.dir.z, 2);
	float	b;
	float	c;
	float	disc;
	t_cyl	xs;

	if (a == 0.0)
		return ((t_cyl){0, 0});
	b = powf(r.origin.x, 2) + 2 * powf(r.origin.z, 2);
	c = (r.origin.x * r.origin.x) + (r.origin.z * r.origin.z) -  cy.diameter/2;
	disc = powf(b, 2) - 4 * a * c;
	if (disc < 0)
		return ((t_cyl){0, 0});
	xs.t0 = (-b - sqrtf(disc)) / (2 * a);
	xs.t1 = (-b + sqrtf(disc)) / (2 * a);
	return (xs);
}

// t is used to determine point p which then can be used to find the normal
// using the formua's demonstrated in the following diagram. The vector |n| needs
// to be normalized or else the shading wont work properly.
float hit_cylinder(t_ray r, t_cylinder cy)
{
	t_cyl	xs;
	t_cyl	ct;
	float	y0;
	float	y1;
	const t_quat q = quaternion_from_axis((t_vec3){0,1,0}, cy.orientation);
	const t_quat inv_q = (t_quat){{-q.v.x, -q.v.y, -q.v.z}, q.w};
	const t_vec3 local_origin = quat_rot(inv_q, vec3_subtract(r.origin, cy.pos));
	const t_vec3 local_dir = quat_rot(inv_q, r.dir);
	const t_ray local_ray = {local_origin, local_dir};

	xs = intersect_cylinder(local_ray, cy);
	ct = intersect_caps(local_ray, cy);
	y0 = local_ray.origin.y + xs.t0 * local_ray.dir.y;
	y1 = local_ray.origin.y + xs.t1 * local_ray.dir.y;
	if (ct.t0)
		return (ct.t0);
	if (ct.t1)
		return (ct.t1);
	if ((cy.min < y0 && y0 < cy.max))
		return (xs.t0);
	if ((cy.min < y1 && y1 < cy.max))
		return (xs.t1);
	return (0);
}
