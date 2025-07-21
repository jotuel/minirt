#include "../include/minirt.h"
#include <unistd.h>

static void convert_prerender(t_map *map)
{
	convert_cylinders(map);
	convert_cylinders(map);
	convert_camera(map->camera);
}

static bool	setup_mlx(t_map *map, int32_t *index)
{
	map->mlx = mlx_init(1200, 800, "minirt", true);
	if (!map->mlx)
		return (false);
	map->img = mlx_new_image(map->mlx, 1200, 800);
	if (!map->img)
	{
		mlx_terminate(map->mlx);
		return (false);
	}
	*index = mlx_image_to_window(map->mlx, map->img, 0, 0);
	if (*index < 0)
	{
		mlx_terminate(map->mlx);
		mlx_delete_image(map->mlx, map->img);
		return (false);
	}
	mlx_set_window_limit(map->mlx, 120, 60, -1, -1);
	return (true);
}

void	cast_rays(void *ptr);
void	key_hook(mlx_key_data_t key, void *map);
void	scroll_hook(double x_delta, double y_delta, void *cam);
void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods,
			void *map);
void	resize_hook(int width, int height, void *map);

static void free_all(t_map *map)
{
	free(map->cy);
	free(map->sp);
	free(map->pl);
}

static int	init_scene(t_map *map, int32_t index)
{
	if (!setup_mlx(map, &index))
		return (1);
	convert_prerender(map);
	mlx_loop_hook(map->mlx, cast_rays, map);
	mlx_key_hook(map->mlx, key_hook, map);
	mlx_resize_hook(map->mlx, resize_hook, map);
	mlx_scroll_hook(map->mlx, scroll_hook, map->camera);
	mlx_mouse_hook(map->mlx, mouse_hook, map);
	mlx_loop(map->mlx);
	mlx_terminate(map->mlx);
	free_all(map);
	return (0);
}

int	main(int argc, char **argv)
{
	t_list	*lst;
	t_map	*map;

	if (argc != 2)
		return (1);
	lst = parse_file(argv[1]);
	if (!lst)
		return (1);
	lst = ft_lstmap(lst, move_to_structs, free);
	if (!lst)
		return (1);
	map = lst->content;
	ft_lstclear(&lst, brush);
	return (init_scene(map, 0));
}
