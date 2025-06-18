#include "../../include/minirt.h"

bool validate_camera(char *line, t_camera cam)
{
    (void)line;
    (void)cam;
    return (true);
}

/*  C    -50,0,0   0,0,1    70 <- example of given camera coordinates
 *	cam  x, y, z  direction fov
 *
*/
void camera(char *line, t_list *lst, t_camera cam)
{
    char **split;
    char **vec;
    char **vec3;

    split = split_and_check(line, '\t', 4, lst);
    vec3 = split_and_check(split[1], ',', 3, lst);
    vec = split_and_check(split[2], ',', 3, lst);
    set_vec3(vec3, &cam.lookfrom);
    set_vec3(vec, &cam.lookat);
    free_split(split);
    free_split(vec3);
    free_split(vec);
    cam.fov = ft_atoi(split[3]);
    if (validate_camera(line, cam))
    	ft_lstadd_front(&lst, ft_lstnew(&cam));
    else
        ft_error(lst);
}
