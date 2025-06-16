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

// adding hittable objects to linkedlist with enum types and creating a function call
// that recognices which object was hit and goes to the right function
// it should remember the closest hit ray position and color that pos
t_intersection intersections(t_ray r, t_node *nodes)
{
	t_type	type;
	t_obj	*obj;
	t_node	*node;
	float	t;
	float	tmin;

	t = 0;
	node = nodes;
	obj = NULL;
	tmin = __FLT_MAX__;
	type = NONE;
	(void)r;
	while (node != NULL)
	{
		if (node->type == SPHERE)
		{
			if (node->obj != NULL)
				t = hit_sphere((t_point)node->obj->sphere.pos, node->obj->sphere.diameter, r);
			if (t > 0.0 && t < tmin)
			{
				tmin = t;
				type = SPHERE;
				obj = node->obj;
			}
		}
		if (node->type == CYLINDER)
		{
			t = hit_cylinder(node->obj->cylinder, r);
			if (t > 0.0 && t < tmin)
			{
				tmin = t;
				type = CYLINDER;
				obj = node->obj;
			}
		}
		if (node->type == PLANE)
		{
			t = color_plane(r);
			if (t > 0.0 && t < tmin)
			{
				tmin = t;
				type = PLANE;
				obj = node->obj;
			}
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
	
	// adding hittable obcts linkedlist/array with sphere types
	// function calls
	// color pixel from the closest hit ray
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
