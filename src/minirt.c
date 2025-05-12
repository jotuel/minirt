#include "../include/minirt.h"

void pixel(void *ptr)
{
    static int a;

    ft_memset(ptr, a, 400);
    a++;
}

void pixel1(void *ptr)
{
    static uint8_t a;

    ft_memset(ptr, a, 400);
    a++;
}

void pixel2(void *ptr)
{
    static uint8_t a;

    ft_memset(ptr, a, 400);
    a++;
}

void pixel3(void *ptr)
{
    static uint8_t a;

    ft_memset(ptr, a, 400);
    a++;
}

int main(int argc, char **argv)
{
	mlx_t *mlx;
	mlx_image_t *img;
	t_map minirt;
	int instance;

	(void)argc;
	minirt = (t_map){0};
	minirt = parse_file(argv[1], minirt);
	if (!minirt.space)
	    return (EXIT_FAILURE);
	mlx = mlx_init(200, 200, "mlx", true);
	img = mlx_new_image(mlx, 200, 200);
	instance = mlx_image_to_window(mlx, img, 0, 0);
	(void)instance;
	mlx_loop_hook(mlx, pixel, img->pixels);
	mlx_loop_hook(mlx, pixel1, &img->pixels[400]);
	mlx_loop_hook(mlx, pixel2, &img->pixels[800]);
	mlx_loop_hook(mlx, pixel3, &img->pixels[1200]);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
