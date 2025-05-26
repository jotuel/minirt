#include "../include/minirt.h"

bool validate_camera(char *line, t_camera cam)
{
    if (!validate_line(line))
        return (false);
    (void)cam;
    return (true);
}


// what type should aspectratio be? its 19:8?
// height will be calculated based on the width and the aspectratio
// but height should never be less than 1
int calculate_height(int width, int aspectratio)
{
	int height;

	height = width / aspectratio;
	if (height < 1)
		height = 1;
	return (height);
}

// C    -50,0,0   0,0,1    70 <- example of given camera coordinates
// camera, position, orientation, horizontal field of view
// this doesnt return anything. Shoudnt it?
void camera(char *line, t_map *rt, t_camera cam)
{
    char **split; // this is the line?
    char **vec;	// this the orientation?
    char **vec3; // this is pos?

    split = split_and_check(line, '\t', 4, rt->space);
    vec3 = split_and_check(split[1], ',', 3, rt->space);
    vec = split_and_check(split[2], ',', 3, rt->space);
    set_vec3(vec3, &cam.pos);
    set_vec3(vec, &cam.orientation);
    free_split(split);
    free_split(vec3);
    free_split(vec);
    cam.fov = ft_atoi(split[3]);
    if (validate_camera(line, cam))
        rt->obj[rt->nbr]->cam = cam;
    else
        ft_error(rt->space);
    rt->obj[rt->nbr]->shape = CAMERA;
}
