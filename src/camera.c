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
	const float	focal_length = length(subtract(cam->lookfrom,
				cam->lookat));
	const float	theta = to_radians(cam->fov);
	const float	h = tanf(theta / 2);
	const float	viewport_height = 2 * h * focal_length;
	const float	viewport_width = viewport_height * img->width / img->height;

	cam->w = cam->lookat;
	cam->u = unit(cross(cam->w, cam->vup));
	cam->v = cross(cam->w, cam->u);
	cam->vu = scale(cam->u, viewport_width);
	cam->vv = scale(neg(cam->v), viewport_height);
	cam->pixel_delta_u = divide(cam->vu, img->width);
	cam->pixel_delta_v = divide(cam->vv, img->height);
	cam->vul = subtract(subtract(subtract(cam->lookfrom,
					scale(cam->w, focal_length)), scale(cam->vu,
					0.5)), scale(cam->vv, 0.5));
	cam->p00 = add(cam->vul, scale(add(cam->pixel_delta_u,
					cam->pixel_delta_v), 0.5));
}
