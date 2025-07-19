#include "../../include/minirt.h"

void	validate_camera(char *line, t_camera cam, t_list *lst)
{
	static int nbr;

	if (nbr++)
		ft_error(lst);
	else if (ft_strncmp(ft_strchr(line, 'C'), "C\t", 2))
		ft_error(lst);
	else if (cam.fov < 1 || cam.fov > 180)
		ft_error(lst);
	else if (0 == vec3_dot(cam.lookat, cam.lookat))
		ft_error(lst);
}

/*  C    -50,0,0   0,0,1    70 <- example of given camera coordinates
 *	cam  x, y, z  direction fov
 *
 */
t_list	*camera(char *line, t_list *lst, t_camera cam)
{
	char	**split;
	char	**vec3;

	split = split_and_check(line, '\t', 4, (void *[]){lst, NULL, line});
	cam.fov = ft_atoi(split[3]);
	vec3 = split_and_check(split[1], ',', 3, (void *[]){lst, split, line});
	set_vec3(vec3, &cam.lookfrom);
	free_split(vec3);
	vec3 = split_and_check(split[2], ',', 3, (void *[]){lst, NULL, line});
	set_vec3(vec3, &cam.lookat);
	free_split(vec3);
	free_split(split);
	validate_camera(line, cam, lst);
	return (ft_lstnew(obj((t_obj){.cam = cam, .type = CAM}, lst)));
}
