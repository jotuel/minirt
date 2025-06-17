#include "../include/minirt.h"
#include <stdint.h>

// this isnt used right now
typedef struct s_hit
{
	t_point	p;
	t_vec3	normal;
	float	t;
}				t_hit;

// returns the point at the distance t along the ray
// position function
static t_point at(t_ray r, float t)
{
	return (vec3_add(r.origin, vec3_scale(r.dir, t)));
}

// should return t and not color
static float color_plane(t_ray r)
{
	float	t;

	t = intersect_plane((t_vec3){0,0,-3.0}, (t_vec3){0,0,1}, r);
	if (t > 0.0)
		return (t);
	return (0);
}


typedef struct s_cyl
{
	float	t0;
	float	t1;
}				t_cyl;

// bool	check_cap(t_ray r, float t)
// {
// 	float	x;
// 	float	z;

// 	x = r.origin.x + t * r.dir.x;
// 	z = r.origin.z + t * r.dir.z;
// 	//1 = diameter
// 	return (((powf(x, 2) + powf(z, 2)) <= 1));
// }
// //TODO: instead of returning t once, both need to be checked and returned
// t_cyl	intersect_caps(t_cylinder cy, t_ray r)
// {
// 	t_cyl 	ct;
// 	float	t;

// 	ct = (t_cyl){0};
// 	if (cy.closed == false || (r.dir.y <= 0.00001))
// 		return (ct);
// 	cy.max = cy.pos.z + cy.max;
// 	cy.min = cy.pos.z + cy.min;
// 	t = (cy.min - r.origin.z) / r.dir.z;
// 	printf("%f\n", t);
// 	if (check_cap(r, t))
// 	{
// 		ct.t0 = t;
// 		printf("cap 1\n");
// 	}
// 	t = (cy.max - r.origin.z) / r.dir.z;
// 	if (check_cap(r, t))
// 	{
// 		printf("cap 2\n");
// 		ct.t1 = t;
// 	}
// 	return (ct);
// }

// //cylinder pos and orientation
// // float cy.diameter
// // float cy.height
// t_cyl intersect_cylinder(t_cylinder cy, t_ray r)
// {
// 	float	a;
// 	float	b;
// 	float	c;
// 	float	disc;
// 	t_cyl	xs;
// 	t_vec3	pos;

// 	pos = vec3_subtract(r.origin, cy.pos);
// 	a =  powf(r.dir.x, 2) + powf(r.dir.z, 2);
// 	if (a == 0.0)
// 		return ((t_cyl){0, 0});
// 	b = 2 * pos.x * r.dir.x + 2 * pos.z * r.dir.z;
// 	c = (pos.x * pos.x) + (pos.z * pos.z) - cy.diameter/2;
// 	disc = (b * b) - 4 * a * c;
// 	if (disc < 0)
// 		return ((t_cyl){0, 0});
// 	xs.t0 = (-b - sqrtf(disc)) / (2 * a);
// 	xs.t1 = (-b + sqrtf(disc)) / (2 * a);
// 	return (xs);
// }


// // t is used to determine point p which then can be used to find the normal
// // using the formua's demonstrated in the following diagram. The vector |n| needs
// // to be normalized or else the shading wont work properly.
// float hit_cylinder(t_cylinder cy, t_ray r)
// {
// 	t_cyl	xs;
// 	t_cyl	ct;
// 	float	y0;
// 	float	y1;

// 	xs = intersect_cylinder(cy, r);
// 	ct = intersect_caps(cy, r);
// 	cy.max = cy.pos.y + cy.max;
// 	cy.min = cy.pos.y + cy.min;
// 	y0 = r.origin.y + xs.t0 * r.dir.y;
// 	y1 = r.origin.y + xs.t1 * r.dir.y;
// 	if (ct.t0)
// 		return (ct.t0);
// 	if (ct.t1)
// 		return (ct.t1);
// 	if ((cy.min < y0 && y0 < cy.max))
// 		return (xs.t0);
// 	if ((cy.min < y1 && y1 < cy.max))
// 		return (xs.t1);
// 	return (0);
// }


// adding hittable objects to linkedlist with enum types and creating a function call
// that recognices which object was hit and goes to the right function
// it should remember the closest hit ray position and color that pos
t_intersection intersections(t_ray r, t_node *node)
{
	t_type	type;
	t_obj	*obj;
	float	t;
	float	tmin;

	t = 0;
	obj = NULL;
	tmin = __FLT_MAX__;
	type = NONE;
	while (node != NULL)
	{
		if (node->type == SPHERE)
			t = hit_sphere(node->obj->sphere.pos, node->obj->sphere.diameter, r);
		if (node->type == CYLINDER)
			t = hit_cylinder(node->obj->cylinder, r);
		if (node->type == PLANE)
			t = color_plane(r);
		if (t > 0.0 && t < tmin)
		{
			tmin = t;
			type = node->type;
			obj = node->obj;
		}
		node = node->next;
	}
	return ((t_intersection) {.type = type, .t = tmin, .obj = obj});
}

// this works but it doesnt take account what is the closest ray hit so that is why
// it only renders one object at time
uint_fast32_t color_ray(t_ray r, t_node *nodes)
{
	float a;
	t_vec3 unit_dir;
	t_intersection hit;
	
	hit = intersections(r, nodes);
	if (hit.type == SPHERE)
	{
		unit_dir = vec3_unit(vec3_subtract(at(r, hit.t), hit.obj->sphere.pos));
		unit_dir = vec3_scale(vec3_add(unit_dir, (t_vec3){1,1,1}), .5f);
		return (get_color((t_color){unit_dir.x*255, unit_dir.y*255, unit_dir.z*255}));
	}
	else if (hit.type == CYLINDER)
	{
		unit_dir = vec3_unit(vec3_subtract(at(r, hit.t), (t_vec3){hit.obj->cylinder.pos.x, at(r, hit.t).y, hit.obj->cylinder.pos.z}));
		unit_dir = vec3_scale(vec3_add(unit_dir, (t_vec3){1,0,1}), .5f);
		return (get_color((t_color){unit_dir.x*255, 0, unit_dir.z*255}));
	}
	else if (hit.type == PLANE)
		return (-1);
	else // only gradient background
	{
		a = 0.5*(vec3_unit(r.dir).y + 1.0);
		unit_dir = (vec3_add(vec3_scale((t_vec3){1.,1.,1}, 1.-a), vec3_scale((t_vec3){0.5,0.7,1.}, a)));
		unit_dir = vec3_scale(unit_dir, 255);
		return (get_color((t_color){unit_dir.x, unit_dir.y, unit_dir.z}));
	}
}

// intersect_sphere
float  hit_sphere(t_point center, float radius, t_ray r)
{
	t_vec3 oc;
	float a;
	float h;
	float c;
	float discrimant;

	oc = vec3_subtract(center, r.origin);
	a = vec3_length(r.dir);
	a *= a;
	h = vec3_dot(r.dir, oc);
	c = vec3_length(oc);
	c = c * c - radius * radius;
	discrimant =  h * h - a * c;
	if (discrimant < 0)
		return (-1.);
	return ((h - sqrtf(discrimant)) / a);
}
