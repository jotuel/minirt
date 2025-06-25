#include "../include/minirt.h"

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
	const float focal_length =
		vec3_length(vec3_subtract(camera->lookfrom, camera->lookat));
	const float theta = to_radians(camera->fov / 2.);
	const float h = tanf(theta / 2);
	const float viewport_height = 2 * h * focal_length;
	const float viewport_width = viewport_height * img->width / img->height;
	t_vec3		viewport_u;
	t_vec3		viewport_v;
	t_vec3		viewport_upper_left;

	camera->w = vec3_unit(vec3_subtract(camera->lookfrom, camera->lookat));
	camera->u = vec3_unit(vec3_cross(camera->vup, camera->w));
	camera->v = vec3_cross(camera->w, camera->u);
	viewport_u = vec3_scale(camera->u, viewport_width);
	viewport_v = vec3_scale(vec3_scale(camera->v, -1), viewport_height);
	camera->pixel_delta_u = vec3_scale(viewport_u, 1. / img->width);
	camera->pixel_delta_v = vec3_scale(viewport_v, 1. / img->height);
	viewport_upper_left = vec3_subtract(vec3_subtract(vec3_subtract(
		camera->lookfrom, vec3_scale(camera->w, focal_length)
	), vec3_scale(viewport_u, 0.5)), vec3_scale(viewport_v, 0.5));
	camera->pixel00_pos = vec3_add(
		viewport_upper_left, vec3_scale(
		vec3_add(camera->pixel_delta_u, camera->pixel_delta_v), 0.5));
}
