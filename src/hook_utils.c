#include "../include/minirt.h"

void	key_util(mlx_key_data_t key, t_map *map)
{
	if (key.key == MLX_KEY_SPACE && (key.modifier & MLX_SHIFT))
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
		map->camera->lookfrom = subtract(map->camera->lookfrom,
				scale(map->camera->lookat, 0.1));
	else if (key.key == MLX_KEY_S)
		map->camera->lookfrom = add(map->camera->lookfrom,
				scale(map->camera->lookat, 0.1));
	else if (key.key == MLX_KEY_A)
		map->camera->lookfrom = subtract(map->camera->lookfrom,
				scale(cross(map->camera->lookat, map->camera->vup), 0.1));
	else if (key.key == MLX_KEY_D)
		map->camera->lookfrom = add(map->camera->lookfrom,
				scale(cross(map->camera->lookat, map->camera->vup), 0.1));
}

bool	rotate_object(mlx_key_data_t key, t_map *map)
{
	if (!map->select)
		return (true);
	else if (key.key == MLX_KEY_Z && key.modifier == MLX_SHIFT)
		rotate_z(map, true);
	else if (key.key == MLX_KEY_Z)
		rotate_z(map, false);
	else if (key.key == MLX_KEY_X && key.modifier == MLX_SHIFT)
		rotate_x(map, true);
	else if (key.key == MLX_KEY_X)
		rotate_x(map, false);
	else if (key.key == MLX_KEY_Y && key.modifier == MLX_SHIFT)
		rotate_y(map, true);
	else if (key.key == MLX_KEY_Y)
		rotate_y(map, false);
	else
		return (false);
	return (true);
}

bool	translate_object(mlx_key_data_t key, t_map *map)
{
	if (key.key == MLX_KEY_KP_5)
		translate_x(map, false);
	else if (key.key == MLX_KEY_KP_8)
		translate_x(map, true);
	else if (key.key == MLX_KEY_KP_4)
		translate_y(map, false);
	else if (key.key == MLX_KEY_KP_6)
		translate_y(map, true);
	else if (key.key == MLX_KEY_KP_7)
		translate_z(map, false);
	else if (key.key == MLX_KEY_KP_9)
		translate_z(map, true);
	else
		return (false);
	return (true);
}
