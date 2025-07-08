#include "../include/minirt.h"

void key_hook(mlx_key_data_t key, t_map *map)
{
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_close_window(map->mlx);
	else if (key.key == MLX_KEY_SPACE && (key.modifier & MLX_SHIFT))
		map->camera->lookfrom.z += 0.1;
	else if (key.key == MLX_KEY_SPACE)
		map->camera->lookfrom.z -= 0.1;
	else if (key.key == MLX_KEY_LEFT)
		map->camera->lookfrom.x -= 0.1;
	else if (key.key == MLX_KEY_RIGHT)
		map->camera->lookfrom.x += 0.1;
	else if (key.key == MLX_KEY_UP)
		map->camera->lookfrom.y += 0.1;
	else if (key.key == MLX_KEY_DOWN)
		map->camera->lookfrom.y -= 0.1;
}

void scroll_hook(double x_delta, double y_delta, t_camera *cam)
{
	if (y_delta > 0 && cam->fov > 4)
		cam->fov -= 5;
	else if (y_delta < 0 && cam->fov < 175)
		cam->fov += 5;
	(void)x_delta;
}
