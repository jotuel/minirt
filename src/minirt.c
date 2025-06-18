#include "../include/minirt.h"
#include <stdint.h>

struct cam_and_img {
	t_camera *cam;
	mlx_image_t *img;
	t_map *minirt;
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
			t_ray ray = (t_ray){.origin = a->cam->lookfrom, .dir = ray_direction};
			mlx_put_pixel(a->img, i, j, color_ray(ray, a->minirt->nodes));
		}
	}
}

// this info needs to come somehow from the parsing
void adding_info_to_nodes(t_map *minirt)
{
	t_node *node;

	node = minirt->nodes;
	if (node->obj != NULL)
	{
		node->obj->sphere.pos = (t_vec3){-.25,-0.25,-2};
		node->obj->sphere.diameter = 0.3;
		node->type = SPHERE;
	}
	node = node->next;
	if (node->obj != NULL)
	{
		node->obj->sphere.pos = (t_vec3){0,1,-6};
		node->obj->sphere.diameter = 0.6;
		node->type = SPHERE;
	}
	node = node->next;
	if (node->obj != NULL)
	{
		node->obj->cylinder.pos = (t_vec3){0,1,-7};
		node->type = CYLINDER;
		node->obj->cylinder.diameter = 10;
		node->obj->cylinder.orientation = (t_vec3){0,0,-1};
		node->obj->cylinder.height = 1.0;
		node->obj->cylinder.max = node->obj->cylinder.height/2;
		node->obj->cylinder.min = -node->obj->cylinder.height/2;
		node->obj->cylinder.closed = false;
	}
}

// struct s {
// 	t_list *sp;
// 	t_list *cy;
// 	t_list *l;
// 	t_list *amb;
// 	t_list *
// }

// int create_nodes(t_list *minirt)
// {

// 	nodes = NULL;
// 	nodes = ft_lstmap(minirt, );
// 	minirt = minirt->next;
// 	adding_info_to_nodes(minirt);
// 	return (0);
// }

int main(int argc, char **argv)
{
	struct cam_and_img a;
	t_camera camera = (t_camera){.lookat = {0,0,-1}, .vup = {0, 1, 0}, .fov  = 90};
	mlx_t *mlx;
	mlx_image_t *img;
	(void)argv;
	t_list *lst;

	if (argc != 2)
		return 1;
	lst = parse_file(argv[1]);
	if(!lst)
		return 1;
//	create_nodes(lst);

	mlx = mlx_init(2000, 1050, "mlx", true);
	img = mlx_new_image(mlx, 2000, 1050);
	mlx_image_to_window(mlx, img, 0, 0);
	a.cam = &camera;
	a.img = img;
	mlx_loop_hook(mlx, render, &a);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
