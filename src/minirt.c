#include "../include/minirt.h"
#include <stdint.h>

struct cam_and_img {
	t_camera *cam;
	mlx_image_t *img;
};

void render(void *ptr)
{
	struct cam_and_img *a;

	a = ptr;
	initialize_camera(a->cam, a->img);
	for(unsigned int j = 0; j < a->img->height; j++) {
		for(unsigned int i = 0; i < a->img->width; i++) {
			t_vec3 p_cen = vec3_add(vec3_add(a->cam->pixel00_pos, vec3_scale(a->cam->pixel_delta_u, i)), vec3_scale(a->cam->pixel_delta_v, j));
			t_vec3 ray_direction =  vec3_subtract(p_cen, (t_vec3){0,0,0});
			t_ray ray = (t_ray){.origin = {0, 0, 0}, .dir = ray_direction};
			mlx_put_pixel(a->img, i, j, color_ray(ray));
		}
	}
}



int main(int argc, char **argv)
{
	struct cam_and_img a;
	t_camera camera = (t_camera){.lookat = {0,0,-1}, .vup = {0, 1, 0}, .fov  = 180};
	mlx_t *mlx;
	mlx_image_t *img;
	// static t_map minirt;
	(void)argv;
	(void)argc;
	// int instance;

	// (void)argc;
	// minirt = (t_map){0};
	// parse_file(argv[1], &minirt);
	// if (!minirt.space)
	//     return (EXIT_FAILURE);

	mlx = mlx_init(800, 600, "mlx", true);
	img = mlx_new_image(mlx, 800, 600);
	mlx_image_to_window(mlx, img, 0, 0);
	a.cam = &camera;
	a.img = img;
	mlx_loop_hook(mlx, render, &a);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
