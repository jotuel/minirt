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
			p_cen = vec3_add(vec3_add(map->camera->pixel00_pos,
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

int	main(int argc, char **argv)
{
	mlx_t	*mlx;
	t_list	*lst;
	t_map	*map;

	(void)argv;
	if (argc != 2)
		return (1);
	lst = parse_file(argv[1]);
	if (!lst)
		return (1);
	lst = ft_lstmap(lst, move_to_structs, free);
	map = lst->content;
	ft_lstclear(&lst, brush);
	mlx = mlx_init(1200, 800, "minirt", true);
	map->img = mlx_new_image(mlx, 1200, 800);
	mlx_image_to_window(mlx, map->img, 0, 0);
	map->camera->vup = (t_vec3){0., 1., 0.};
	mlx_loop_hook(mlx, cast_rays, map);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
