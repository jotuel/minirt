#include "../include/minirt.h"
#include <stdint.h>

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
	if (hit.type == CYLINDER)
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
