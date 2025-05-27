#include "../include/minirt.h"

void render(void *ptr)
{
	mlx_image_t *img;

	img = ptr;
	(void)img;
}

int main(int argc, char **argv)
{
	mlx_t *mlx;
	mlx_image_t *img;
	static t_map minirt;
	int instance;

	(void)argc;
	minirt = (t_map){0};
	parse_file(argv[1], &minirt);
	if (!minirt.space)
	    return (EXIT_FAILURE);
	mlx = mlx_init(200, 200, "mlx", true);
	img = mlx_new_image(mlx, 200, 200);
	instance = mlx_image_to_window(mlx, img, 0, 0);
	(void)instance;
	mlx_loop_hook(mlx, render, img->pixels);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
