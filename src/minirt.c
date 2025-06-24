#include "../include/minirt.h"
#include <stdint.h>

void cast_rays(void *ptr)
{
    t_map *map = ptr;
    unsigned int w;
    unsigned int h;

    initialize_camera(&map->camera, map->img);
    w = 0;
    h = 0;
    while(w < map->img->width)
    {
        while(h < map->img->height)
        {
            t_vec3 p_cen = vec3_add(vec3_add(map->camera.pixel00_pos, vec3_scale(map->camera.pixel_delta_u, h)), vec3_scale(map->camera.pixel_delta_v, w));
			t_vec3 ray_direction =  vec3_subtract(p_cen, (t_vec3){0,0,0});
			t_ray ray = (t_ray){.origin = map->camera.lookfrom, .dir = ray_direction};
            mlx_put_pixel(map->img, w, h, color_ray(ray, map));
            h += 1;
        }
        h = 0;
        w += 1;
    }
}

int main(int argc, char **argv)
{
	mlx_t *mlx;
	mlx_image_t *img;
	(void)argv;
	t_list *lst;
	t_map *map;

	if (argc != 2)
		return 1;
	lst = parse_file(argv[1]);
	if(!lst)
		return 1;
	lst = ft_lstmap(lst, move_to_structs, free);
	map = lst->content;
	mlx = mlx_init(400, 150, "mlx", true);
	img = mlx_new_image(mlx, 400, 150);
	mlx_image_to_window(mlx, img, 0, 0);
	map->img = img;
	mlx_loop_hook(mlx, cast_rays, map);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
