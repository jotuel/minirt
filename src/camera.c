#include "../include/minirt.h"

// what type should aspectratio be? its 19:8?
// height will be calculated based on the width and the aspectratio
// but height should never be less than 1
int	calculate_height(int width, float aspectratio)
{
	int	height;

	height = width / aspectratio;
	if (height < 1)
		height = 1;
	return (height);
}

/// @brief camera is initialized after the other objects are
/// located to the scene relative to the camera coordinates
void	initialize_camera(t_camera *cam, mlx_image_t *img)
{
	const float	focal_length = vec3_length(vec3_subtract(cam->lookfrom,
				cam->lookat));
	const float	theta = to_radians(cam->fov / 2.);
	const float	h = tanf(theta / 2);
	const float	viewport_height = 2 * h * focal_length;
	const float	viewport_width = viewport_height * img->width / img->height;

	cam->w = vec3_unit(vec3_subtract(cam->lookfrom, cam->lookat));
	cam->u = vec3_unit(vec3_cross(cam->vup, cam->w));
	cam->v = vec3_cross(cam->w, cam->u);
	cam->vu = vec3_scale(cam->u, viewport_width);
	cam->vv = vec3_scale(vec3_scale(cam->v, -1), viewport_height);
	cam->pixel_delta_u = vec3_scale(cam->vu, 1. / img->width);
	cam->pixel_delta_v = vec3_scale(cam->vv, 1. / img->height);
	cam->vul = vec3_subtract(vec3_subtract(vec3_subtract(cam->lookfrom,
					vec3_scale(cam->w, focal_length)), vec3_scale(cam->vu,
					0.5)), vec3_scale(cam->vv, 0.5));
	cam->pixel00_pos = vec3_add(cam->vul,
			vec3_scale(vec3_add(cam->pixel_delta_u, cam->pixel_delta_v), 0.5));
}
