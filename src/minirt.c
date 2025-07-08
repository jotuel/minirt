#include "../include/minirt.h"
#include <stdint.h>

void	cast_rays(void *ptr)
{
	t_map			*map;
	unsigned int	w;
	unsigned int	h;
	t_vec3			p_cen;
	t_ray			ray;

	map = ptr;
	initialize_camera(map->camera, map->img);
	w = 0;
	h = 0;
	while (w < map->img->width)
	{
		while (h < map->img->height)
		{
			p_cen = vec3_add(vec3_add(map->camera->p00,
						vec3_scale(map->camera->pixel_delta_u, h)),
					vec3_scale(map->camera->pixel_delta_v, w));
			ray = (t_ray){.origin = map->camera->lookfrom,
				.dir = vec3_unit(vec3_subtract(p_cen,
							map->camera->lookfrom))};
			mlx_put_pixel(map->img, w, h, color_ray(ray, map));
			h += 1;
		}
		h = 0;
		w += 1;
	}
}

void key_hook(mlx_key_data_t key, void *map);
void scroll_hook(double x_delta, double y_delta, void *cam);

int init_scene(t_map *map, 	int32_t	index)
{
	map->camera->vup = (t_vec3){0., 1., 0.};
	map->mlx = mlx_init(1200, 800, "minirt", false);
	if (!map->mlx)
		return (1);
	map->img = mlx_new_image(map->mlx, 1200, 800);
	if (!map->img)
		return (mlx_terminate(map->mlx), 1);
	index = mlx_image_to_window(map->mlx, map->img, 0, 0);
	if (index < 0)
		return (mlx_terminate(map->mlx), mlx_delete_image(map->mlx, map->img), 1);
	if (!mlx_loop_hook(map->mlx, cast_rays, map))
		return (1);//mlx_terminate(map->mlx), mlx_delete_image(map->mlx, map->img), 1);
	mlx_key_hook(map->mlx, key_hook, map);
	mlx_scroll_hook(map->mlx, scroll_hook, map->camera);
	mlx_loop(map->mlx);
//	mlx_delete_image(map->mlx, map->img);
//	mlx_terminate(map->mlx);
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
