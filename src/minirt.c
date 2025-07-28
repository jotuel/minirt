#include "../include/minirt.h"
#include <unistd.h>
#include <emscripten/html5.h>
#include <emscripten/emscripten.h>

mlx_t *mlx;

void	emscripten_main_loop() {
	mlx_loop(mlx);
}

static void	convert_prerender(t_map *map)
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
void	*move_to_structs(void *ptr);
void	key_hook(mlx_key_data_t key, void *map);
void	scroll_hook(double x_delta, double y_delta, void *cam);
void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods,
				void *map);
void	resize_hook(int width, int height, void *map);

static void	free_all(t_map *map)
{
	free(map->cy);
	free(map->sp);
	free(map->pl);
	free(map->ambient);
	free(map->camera);
	free(map->light);
	free(map);
}

static int	init_scene(t_map *map, int32_t index)
{
	map->mlx = mlx;
	if (!(map->camera && map->ambient && map->light))
	{
		free_all(map);
		ft_putendl_fd("Error\nMissing mandatory object", 2);
		return (1);
	}
	if (!setup_mlx(map, &index))
	{
		free_all(map);
		ft_putendl_fd("Error\nMLX42 setup failed", 2);
		return (1);
	}
	convert_prerender(map);
	mlx_loop_hook(map->mlx, cast_rays, map);
	mlx_key_hook(map->mlx, key_hook, map);
	mlx_resize_hook(map->mlx, resize_hook, map);
	mlx_scroll_hook(map->mlx, scroll_hook, map->camera);
	mlx_mouse_hook(map->mlx, mouse_hook, map);
	emscripten_set_main_loop(emscripten_main_loop, 0, true);
	mlx_terminate(map->mlx);
	free_all(map);
	return (0);
}

int	main(int argc, char **argv)
{
	t_list	*lst[2];
	int		ret;

	if (argc != 2)
	{
		ft_putendl_fd("Error\nUsage ./minirt *.rt", 2);
		return (1);
	}
	lst[0] = parse_file(argv[1]);
	if (!lst[0] || !lst[0]->content)
		ft_error(lst[0], "No lines");
	lst[1] = ft_lstmap(lst[0], move_to_structs, free);
	ret = init_scene(lst[1]->content, 0);
	ft_lstclear(&lst[0], free);
	ft_lstclear(&lst[1], brush);
	return (ret);
}
