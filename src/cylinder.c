#include "../include/minirt.h"


//create hit cylinder function
typedef struct s_cyl
{
	float	t0;
	float	t1;
}				t_cyl;

bool	check_cap(t_ray r, float t)
{
	float	x;
	float	z;

	x = r.origin.x + t * r.dir.x;
	z = r.origin.z + t * r.dir.z;
	//1 = diameter
	return (((powf(x, 2) + powf(z, 2)) <= 1));
}

//TODO: instead of returning t once, both need to be checked and returned
t_cyl	intersect_caps(t_cylinder cy, t_ray r)
{
	t_cyl 	ct;
	float	t;

	ct = (t_cyl){0};
	if (cy.closed == false || (r.dir.y <= 0.00001))
		return (ct);
	cy.max = cy.pos.z + cy.max;
	cy.min = cy.pos.z + cy.min;
	t = (cy.min - r.origin.z) / r.dir.z;
	printf("%f\n", t);
	if (check_cap(r, t))
	{
		ct.t0 = t;
		printf("cap 1\n");
	}
	t = (cy.max - r.origin.z) / r.dir.z;
	if (check_cap(r, t))
	{
		printf("cap 2\n");
		ct.t1 = t;
	}
	return (ct);
}

//cylinder pos and orientation
// float cy.diameter
// float cy.height
t_cyl intersect_cylinder(t_cylinder cy, t_ray r)
{
	float	a;
	float	b;
	float	c;
	float	disc;
	t_cyl	xs;
	t_vec3	pos;

	pos = vec3_subtract(r.origin, cy.pos);
	a =  powf(r.dir.x, 2) + powf(r.dir.z, 2);
	if (a == 0.0)
		return ((t_cyl){0, 0});
	b = 2 * pos.x * r.dir.x + 2 * pos.z * r.dir.z;
	c = (pos.x * pos.x) + (pos.z * pos.z) - cy.diameter/2;
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

	xs = intersect_cylinder(cy, r);
	ct = intersect_caps(cy, r);
	cy.max = cy.pos.y + cy.max;
	cy.min = cy.pos.y + cy.min;
	y0 = r.origin.y + xs.t0 * r.dir.y;
	y1 = r.origin.y + xs.t1 * r.dir.y;
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

bool validate_cylinder(char *line, t_cylinder cy)
{
 	(void)line;
    (void)cy;
    return (true);
}

void cylinder(char *line, t_map *rt, t_cylinder cy)
{
    char **split;
    char **vec3;
    char **vec;
    char **colors;

    split = split_and_check(line, '\t', 6, rt->space);
    vec3 = split_and_check(split[1], ',', 3, rt->space);
    vec = split_and_check(split[2], ',', 3, rt->space);
    colors = split_and_check(split[5], ',', 3, rt->space);
    set_vec3(vec3, &cy.pos);
    set_vec3(vec, &cy.orientation);
    set_colors(colors, &cy.color);
    cy.diameter = ft_atof(split[3]);
    cy.height = ft_atof(split[4]);
    free_split(split);
    free_split(vec3);
    free_split(vec);
    free_split(colors);
    if (validate_cylinder(line, cy))
        rt->obj[rt->nbr++]->cylinder = cy;
    else
        ft_error(rt->space);
    rt->obj[rt->nbr]->type = CYLINDER;
}
