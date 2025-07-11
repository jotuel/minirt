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
	else if (key.key == MLX_KEY_W)
		map->camera->lookfrom = vec3_subtract(map->camera->lookfrom, vec3_scale(map->camera->lookat, 0.1));
	else if (key.key == MLX_KEY_S)
		map->camera->lookfrom = vec3_add(map->camera->lookfrom, vec3_scale(map->camera->lookat, 0.1));
	else if (key.key == MLX_KEY_A)
		map->camera->lookfrom = vec3_subtract(map->camera->lookfrom, vec3_scale(vec3_cross(map->camera->lookat, map->camera->vup), 0.1));
	else if (key.key == MLX_KEY_D)
		map->camera->lookfrom = vec3_add(map->camera->lookfrom, vec3_scale(vec3_cross(map->camera->lookat, map->camera->vup), 0.1));
}

void scroll_hook(double x_delta, double y_delta, t_camera *cam)
{
	if (y_delta > 0 && cam->fov > 4)
		cam->fov -= 5;
	else if (y_delta < 0 && cam->fov < 175)
		cam->fov += 5;
	(void)x_delta;
}

void mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, t_map *map)
{
	static int xy[2];
	int x;
	int y;

	if (button == MLX_MOUSE_BUTTON_LEFT || action)
	{
		mlx_get_mouse_pos(map->mlx, &x, &y);
		if (x < xy[0] && map->camera->lookat.z > -0.91)
			map->camera->lookat = vec3_add(map->camera->lookat, vec3_scale(vec3_cross(map->camera->lookat, map->camera->vup), 0.1));
		else if (x > xy[0] && map->camera->lookat.z < 0.91)
			map->camera->lookfrom = vec3_subtract(map->camera->lookat, vec3_scale(vec3_cross(map->camera->lookat, map->camera->vup), 0.1));
		if (y < xy[1] && map->camera->lookat.y > -0.91)
			map->camera->lookat.y += 0.1;
		else if (y > xy[1] && map->camera->lookat.y < 0.91)
			map->camera->lookat.y -= 0.1;
		xy[0] = x;
		xy[1] = y;
	}
	(void)mods;
}

void resize_hook(int width, int height, t_map *map)
{
	if (width > 0 && height > 0)
	{
		map->camera->aspectratio = (float)width / height;
		map->camera->width = width;
		map->camera->height = height;
		mlx_resize_image(map->img, width, height);
	}
}
