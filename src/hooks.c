#include "../include/minirt.h"

/*
 * handle some keystrokes as input
 */
void	key_hook(mlx_key_data_t key, t_map *map)
{
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_close_window(map->mlx);
	else if (rotate_object(key, map))
		return ;
	else if (translate_object(key, map))
		return ;
	else
		key_util(key, map);
}

/*
 * mouse scrolling changes the fov of the camera.
 */
void	scroll_hook(double x_delta, double y_delta, t_camera *cam)
{
	if (y_delta > 0 && cam->fov > 4)
		cam->fov -= 5;
	else if (y_delta < 0 && cam->fov < 175)
		cam->fov += 5;
	(void)x_delta;
}

void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods,
		t_map *map)
{
	static t_isect	is;
	t_vec3			tmp;
	t_ray			ray;
	int				x;
	int				y;

	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		mlx_get_mouse_pos(map->mlx, &x, &y);
		tmp = add(add(map->camera->p00,
					scale(map->camera->pixel_delta_u, y)),
				scale(map->camera->pixel_delta_v, x));
		ray = (t_ray){.origin = map->camera->lookfrom,
			.dir = unit(subtract(tmp, map->camera->lookfrom))};
		is = intersections(ray, map);
		map->select = &is;
	}
	(void)mods;
}

/*
 * resizes the image to match when the window is resized.
 */
void	resize_hook(int width, int height, t_map *map)
{
	map->camera->aspectratio = (float)width / height;
	map->camera->width = width;
	map->camera->height = height;
	mlx_resize_image(map->img, width, height);
}
