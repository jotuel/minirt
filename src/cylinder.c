#include "../include/minirt.h"

typedef struct s_quat
{
	float	w;
	float	x;
	float	y;
	float	z;

}				t_quat;

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
t_cyl	intersect_caps(t_cylinder cy, t_ray r)
{
	t_cyl 	ct;
	float	t;

	ct = (t_cyl){0};
	if (cy.closed == false || (r.dir.y <= 0.00001))
		return (ct);
	t = (cy.min - r.origin.z) / r.dir.z;
	if (check_cap(r, t, cy))
	{
		ct.t0 = t;
	}
	t = (cy.max - r.origin.z) / r.dir.z;
	if (check_cap(r, t, cy))
	{
		ct.t1 = t;
	}
	return (ct);
}

// to normalize a vector we first need the magnitude 
// while maintaining the original direction
// we divide the vec3 by its magnitude.
// we new normalized vector with lenght of 1
// replace with vet3_unit
t_vec3	normalize_vector(t_vec3 v)
{
	const float	magnitude = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);

	return ((t_vec3){v.x / magnitude, v.y / magnitude, v.z / magnitude});
}

t_quat normalize_quat(t_quat q)
{
	const float	magnitude = sqrtf(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);

	return ((t_quat){ q.w / magnitude, q.x / magnitude, q.y / magnitude, q.z / magnitude});
}

t_quat quaternion_from_axis(t_vec3 from, t_vec3 to)
{
	const t_vec3 afrom = normalize_vector(from);
	const t_vec3 bto = normalize_vector(to);
	const float dot = vec3_dot(afrom, bto); // returns a scalar value of two vectors, the angle between them
	const t_vec3 axis = vec3_cross(afrom, bto); //gives me the axis to rotate from?
	const float angle = acosf(dot);
	float s;

	if (dot > 0.9999f) // no rotation needed
		return ((t_quat){1, 0, 0, 0});
	if (dot < -0.9999f) //the dot is -1 which means exactly the mirror rotation
	{// so the above cross production gives {0,0,0} so we find manually axis to rotate the cylinder
		t_vec3 orthogonal = vec3_cross(afrom, (t_vec3){1,0,0});
		if (vec3_length(orthogonal) < 0.0001f)
			orthogonal = vec3_cross(afrom, (t_vec3){0,0,1});
		orthogonal = normalize_vector(orthogonal);
		return ((t_quat){0, orthogonal.x, orthogonal.y, orthogonal.z});
	}
	s = sinf(angle * 0.5f);
	return (normalize_quat((t_quat){.w = cosf(angle * 0.5f), .x = axis.x * s, .y = axis.y * s, .z = axis.z * s}));
}

// s = scalar
t_vec3	rotate_vector_by_quaternion (t_vec3 v, t_quat q)
{
	const t_vec3 u = {q.x, q.y, q.z};
	const float s = q.w;
	t_vec3 new_vector;

	new_vector = vec3_add(vec3_add(vec3_scale(u, vec3_dot(u, v) * 2.0f),
				vec3_scale( v, s*s - vec3_dot(u, u))), vec3_scale(vec3_cross(u, v), 2.0f * s));
	return (new_vector);
}

// cylinder pos and orientation
// float cy.diameter
// float cy.height
t_cyl intersect_cylinder(t_cylinder cy, t_ray r_local)
{
	float	a;
	float	b;
	float	c;
	float	disc;
	t_cyl	xs;

	a =  powf(r_local.dir.x, 2) + powf(r_local.dir.z, 2);
	if (a == 0.0)
		return ((t_cyl){0, 0});
	b = 2 * r_local.origin.x * r_local.dir.x + 2 * r_local.origin.z * r_local.dir.z;
	c = (r_local.origin.x * r_local.origin.x) + (r_local.origin.z * r_local.origin.z) -  cy.diameter/2;
	disc = (b * b) - 4 * a * c;
	if (disc < 0)
		return ((t_cyl){0, 0});
	xs.t0 = (-b - sqrtf(disc)) / (2 * a);
	xs.t1 = (-b + sqrtf(disc)) / (2 * a);
	return (xs);
}

// t is used to determine point p which then can be used to find the normal
// using the formua's demonstrated in the following diagram. The vector |n| needs
// to be normalized or else the shading wont work properly.
float hit_cylinder(t_cylinder cy, t_ray r)
{
	t_cyl	xs;
	t_cyl	ct;
	float	y0;
	float	y1;
	const t_quat q = quaternion_from_axis((t_vec3){0,1,0}, cy.orientation);
	const t_quat inv_q = (t_quat){q.w, -q.x, -q.y, -q.z};
	const t_vec3 local_origin = rotate_vector_by_quaternion(vec3_subtract(r.origin, cy.pos), inv_q);
	const t_vec3 local_dir = rotate_vector_by_quaternion(r.dir, inv_q);
	const t_ray local_ray = {local_origin, local_dir};

	xs = intersect_cylinder(cy, local_ray);
	ct = intersect_caps(cy, local_ray);
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
