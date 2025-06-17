#include "../include/minirt.h"

// static t_point at(t_ray r, float t)
// {
// 	return (vec3_add(r.origin, vec3_scale(r.dir, t)));
// }
//
// should return t and not color
float color_plane(t_ray r)
{
	float	t;

	t = intersect_plane((t_vec3){0,0,-3.0}, (t_vec3){0,0,1}, r);
	if (t > 0.0)
		return (t);
	return (0);
}

float intersect_plane(t_vec3 center, t_vec3 rot, t_ray r)
{
	t_vec3 p0l0;
	float t;
	float denom;

	denom = vec3_dot(center, r.origin);
	if (denom >  1e-6)
		{
			p0l0 = vec3_subtract(rot, r.dir);
			t = vec3_dot(p0l0, center) / denom;
			printf("t:%f\n", t);
			return (t);
		}
	return (-1);
}

bool validate_plane(char *line, t_plane pl)
{
    (void)line;
    (void)pl;
    return (true);
}

void plane(char *line, t_list *lst, t_plane pl)
{
    char **split;
    char **vec3;
    char **vec;
    char **colors;

    split = split_and_check(line, '\t', 4, lst);
    vec3 = split_and_check(split[1], ',', 3, lst);
    vec = split_and_check(split[2], ',', 3, lst);
    colors = split_and_check(split[3], ',', 3, lst);
    set_vec3(vec3, &pl.pos);
    set_vec3(vec, &pl.orientation);
    set_colors(colors, &pl.color);
    free_split(split);
    free_split(vec3);
    free_split(vec);
    free_split(colors);
    if (validate_plane(line, pl))
        ft_lstadd_front(&lst, ft_lstnew(&pl));
    else
        ft_error(lst);
}
