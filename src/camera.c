#include "../include/minirt.h"

bool validate_camera(char *line, t_camera cam)
{
    (void)line;
    (void)cam;
    return (true);
}


// what type should aspectratio be? its 19:8?
// height will be calculated based on the width and the aspectratio
// but height should never be less than 1
int calculate_height(int width, float aspectratio)
{
	int height;

	height = width / aspectratio;
	if (height < 1)
		height = 1;
	return (height);
}

/// @brief camera is initialized after the other objects are
/// located to the scene relative to the camera coordinates
void initialize_camera(t_camera *camera, mlx_image_t *img)
{
	static  t_vec3 vec3;
	float	focal_length;
	float	theta;
	float	h;
	float	viewport_height;
	float	viewport_width;
	t_vec3	viewport_u;
	t_vec3	viewport_v;
	t_vec3	viewport_upper_left;

	camera->aspectratio = (float)img->width/img->height;
	camera->width = img->width;
	camera->height = img->height;
	camera->lookfrom = vec3;
	vec3 = vec3_add(vec3, (t_vec3){0.00,0.00,0.01});
	focal_length = vec3_length(vec3_subtract(camera->lookfrom, camera->lookat));
	theta = to_radians(camera->fov / 2.);
	h = tanf(theta/2);
	viewport_height = 2 * h * focal_length;
	viewport_width = viewport_height * camera->aspectratio;
	camera->w = vec3_unit(vec3_subtract(camera->lookfrom, camera->lookat));
	camera->u = vec3_unit(vec3_cross(camera->vup, camera->w));
	camera->v = vec3_cross(camera->w, camera->u);
	viewport_u = vec3_scale(camera->u, viewport_width);
	viewport_v = vec3_scale(vec3_scale(camera->v, -1), viewport_height);
	camera->pixel_delta_u = vec3_scale(viewport_u, 1. / camera->width);
	camera->pixel_delta_v = vec3_scale(viewport_v, 1. / camera->height);
	viewport_upper_left = vec3_subtract(vec3_subtract(vec3_subtract(camera->lookfrom,
				vec3_scale(camera->w, focal_length)), vec3_scale(viewport_u, 0.5)) , vec3_scale(viewport_v, 0.5));
	camera->pixel00_pos = vec3_add(viewport_upper_left,vec3_scale(vec3_add(camera->pixel_delta_u, camera->pixel_delta_v), 0.5));
}

/*  C    -50,0,0   0,0,1    70 <- example of given camera coordinates
 *	cam  x, y, z  direction fov
 *
*/
void camera(char *line, t_map *rt, t_camera cam)
{
    char **split;
    char **vec;
    char **vec3;

    split = split_and_check(line, '\t', 4, rt->nodes);
    vec3 = split_and_check(split[1], ',', 3, rt->nodes);
    vec = split_and_check(split[2], ',', 3, rt->nodes);
    set_vec3(vec3, &cam.lookfrom);
    set_vec3(vec, &cam.lookat);
    free_split(split);
    free_split(vec3);
    free_split(vec);
    cam.fov = ft_atoi(split[3]);
    if (validate_camera(line, cam))
        rt->obj[rt->nbr]->cam = cam;
    else
        ft_error(rt->nodes);
    rt->obj[rt->nbr]->type = CAMERA;
}
