#include "../include/minirt.h"

bool validate_camera(char *line, t_camera cam)
{
    if (!validate_line(line))
        return (false);
    (void)cam;
    return (true);
}

void camera(char *line, t_map *rt, t_camera cam)
{
    char **split;
    char **vec;
    char **vec3;

    split = split_and_check(line, '\t', 4, rt->space);
    vec3 = split_and_check(split[1], ',', 3, rt->space);
    vec = split_and_check(split[2], ',', 3, rt->space);
    set_vec3(vec3, &cam.pos);
    set_vec3(vec, &cam.orientation);
    cam.fov = ft_atoi(split[3]);
    if (validate_camera(line, cam))
        rt->obj[rt->nbr]->cam = cam;
    else
        ft_error(rt->space);
    rt->obj[rt->nbr]->shape = CAMERA;
}
