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
		node->obj->sphere.pos = (t_vec3){-.5,-0.25,-2};
		node->obj->sphere.diameter = 0.3;
		node->type = SPHERE;
	}
	node = node->next;
	if (node->obj != NULL)
	{
		node->obj->sphere.pos = (t_vec3){-1,1,-6};
		node->obj->sphere.diameter = 0.6;
		node->type = SPHERE;
	}
	node = node->next;
	if (node->obj != NULL)
	{
		node->obj->cylinder.pos = (t_vec3){1,0,-7};
		node->type = CYLINDER;
		node->obj->cylinder.diameter = 1;
		node->obj->cylinder.orientation = (t_vec3){0,0,1};
		node->obj->cylinder.height = 1.0;
		node->obj->cylinder.max = node->obj->cylinder.height/2;
		node->obj->cylinder.min = -node->obj->cylinder.height/2;
		node->obj->cylinder.closed = false;
	}
}

int create_nodes(t_map *minirt)
{
	size_t	size;
	t_node	*new_node;
	t_node	*prev;

	// --- this part will be changed and the info will
	// come from the parsing
	minirt->obj[0] = ft_calloc(sizeof(t_obj), 1);
	minirt->obj[0]->type = SPHERE;
	minirt->obj[1] = ft_calloc(sizeof(t_obj), 1);
	minirt->obj[1]->type = SPHERE;
	minirt->obj[2] = ft_calloc(sizeof(t_obj), 1);
	minirt->obj[2]->type = CYLINDER;
	minirt->nbr = 3;
	// remove above

	prev = NULL;
	size = 0;
	while (size != minirt->nbr)
	{
		new_node = ft_calloc(sizeof(t_node), 1);
		if (!new_node)
			return (1);
		new_node->data = size;
		new_node->next = NULL;
		new_node->type = minirt->obj[size]->type;
		new_node->obj = minirt->obj[size];
		if (prev)
			prev->next = new_node;
		else
			minirt->nodes = new_node;
		prev = new_node;
		size++;
	}
	adding_info_to_nodes(minirt);
	return (0);
}

int main(int argc, char **argv)
{
	struct cam_and_img a;
	t_camera camera = (t_camera){.lookat = {0,0,-1}, .vup = {0, 1, 0}, .fov  = 90};
	mlx_t *mlx;
	mlx_image_t *img;
	static t_map minirt;
	(void)argv;
	(void)argc;

	minirt = (t_map){0};
	// parse_file(argv[1], &minirt);
	create_nodes(&minirt);

	mlx = mlx_init(2000, 1050, "mlx", true);
	img = mlx_new_image(mlx, 2000, 1050);
	mlx_image_to_window(mlx, img, 0, 0);
	a.cam = &camera;
	a.img = img;
	a.minirt = &minirt;
	mlx_loop_hook(mlx, render, &a);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
