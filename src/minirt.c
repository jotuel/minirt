#include "../include/minirt.h"

void	test(void *ptr)
{
    mlx_image_t *image;
	unsigned int x;
	unsigned int y;

	image = ptr;
	x = 0;
	y = 0;
	while (y < image->height)
	{
		while (x < image->width)
		{
			float r = (float)x / (image->width-1);
			float g = (float)y / (image->height-1);

			mlx_put_pixel(image, x, y, ((int)(255.999 * r) << 24 ) + ((int)(255.999 * g) << 16) + 255);
			x++;
		}
		y++;
		x = 0;
	}
}

int main()
{
    mlx_image_t *image;
    mlx_t *mlx;

    mlx = mlx_init(400, 200, "Testing...", false);
    image = mlx_new_image(mlx, 400, 200);
	mlx_image_to_window(mlx, image, 0, 0);
	mlx_loop_hook(mlx, test, image);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

// int main(int argc, char **argv)
// {
// 	mlx_t *mlx;
// 	mlx_image_t *img;
// 	t_map minirt;
// 	int instance;

// 	(void)argc;
// 	minirt = (t_map){0};
// 	minirt = parse_file(argv[1], minirt);
// 	if (!minirt.space)
// 	    return (EXIT_FAILURE);
// 	mlx = mlx_init(400, 200, "mlx", true);
// 	img = mlx_new_image(mlx, 400, 200);
// 	instance = mlx_image_to_window(mlx, img, 0, 0);
// 	(void)instance;
// 	mlx_loop_hook(mlx, pixel, img->pixels);
// 	mlx_loop_hook(mlx, pixel1, &img->pixels[400]);
// 	mlx_loop_hook(mlx, pixel2, &img->pixels[800]);
// 	mlx_loop_hook(mlx, pixel3, &img->pixels[1200]);
// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// }
