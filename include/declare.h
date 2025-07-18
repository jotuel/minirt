#ifndef DECLARE_H
#define DECLARE_H
#include "../MLX42/include/MLX42/MLX42.h"
#include "../libft/libft.h"
#include "types.h"
#include <stdbool.h>

void 			ft_error(void *mem);

/* CASTING RAYS */
float 			hit_sphere(t_ray r, t_sphere sp);
uint_fast32_t	color_ray(t_ray r, t_map *map);
t_intersection	intersections(t_ray r, t_map *map);
t_intersection 	intersect_plane(t_ray r, t_plane pl);
t_intersection	intersect_cylinders(t_ray r, t_object *cy, const unsigned int nbr);
t_intersection	intersect_planes(t_ray r, t_object *pl, const unsigned int nbr);
t_intersection	intersect_spheres(t_ray r, t_object *sp, const unsigned int nbr);
t_intersection	hit_cylinder(t_ray r, t_cylinder cy);
t_vec3 			cylinder_normal(t_vec3 p, t_vec3 a, t_vec3 b, float ra);
void           	initialize_camera(t_camera *camera, mlx_image_t *img);

/* SHADING */
t_color			add_colors(t_color color1, t_color color2);
t_color			specular_color(t_ray r, t_map *map, t_vec3 l_dir, t_vec3 normal);
t_color			diffuse_color(t_intersection hit, t_map *map, t_vec3 l_dir, t_vec3 normal);
t_color			ambient_color(t_intersection hit, t_map *map);
t_color			color_scale(t_color vec, float scale);

/* SET & GET FUNCTIONS */
float			vec3_get_z(t_vec3 vec);
float			vec3_get_x(t_vec3 vec);
float			vec3_get_y(t_vec3 vec);
void			set_quaternion(float w, t_vec3 v, t_quat *q);
void			vec3_set_x(t_vec3 *vec, float x);
void			vec3_set_y(t_vec3 *vec, float y);
void			vec3_set_z(t_vec3 *vec, float z);
void			set_vec3(char **vec3, t_vec3 *vec);
void			set_colors(char **colors, t_color *color);
void			set_red(t_color *color, uint8_t colour);
void			set_green(t_color *color, uint8_t colour);
void			set_blue(t_color *color, uint8_t colour);
uint_fast32_t	get_color(t_color color);
t_color			mix_colors(t_color color1, t_color color2);
uint_fast32_t	pixel_color(void);
t_list			*ambient(char *line, t_list *lst, t_ambient amb);
t_list			*camera(char *line, t_list *lst, t_camera cam);
t_list			*cylinder(char *line, t_list *lst, t_cylinder cy);
t_list			*plane(char *line, t_list *lst, t_plane pl);
t_list			*sphere(char *line, t_list *lst, t_sphere sp);
t_list			*light(char *line, t_list *lst, t_light light);

/* MAP PARSING */
t_list			*parse_file(char *filename);
char			**split_and_check(char *input, char by, int fields, void *mem[3]);
void			free_split(char **split);
void			*obj(t_obj obj, t_list *lst);
void			*move_to_structs(void *ptr);
void			brush(void *ptr);

/* MATH */
t_point			at(t_ray r, float t);
float			lerp(float s, float e, float f);
uint_fast8_t	color_lerp(float f);
float			to_degrees(float radians);
float			to_radians(float degrees);
float			quat_norm(t_quat q);
t_quat			quat_normalize(t_quat q);
t_vec3			quat_rot(t_quat q, t_vec3 v);
t_quat			to_quaternion(t_vec3 v);
t_quat			quaternion_from_axis(t_vec3 from, t_vec3 to);
t_vec3			rotate_vector_by_quaternion (t_vec3 v, t_quat q);

/* VECTOR MATH */
uint_fast32_t	vec3_lerp(t_vec3 v);
t_vec3			vec3_unit(t_vec3 v);
t_vec3			vec3_neg(t_vec3 vec);
t_vec3			vec3_cross(t_vec3 v, t_vec3 w);
t_vec3			vec3_scale(t_vec3 vec, float scale);
float			vec3_length(t_vec3 vec);
float			vec3_dot(t_vec3 v, t_vec3 w);
t_vec3			vec3_add(t_vec3 vec, t_vec3 vec1);
t_vec3			vec3_subtract(t_vec3 vec, t_vec3 vec1);
t_vec3			vec3_multiply(t_vec3 vec, t_vec3 vec1);
t_vec3			vec3_square(t_vec3 vec);
t_vec3			reflection(t_vec3 vec, t_vec3 n);
t_vec3			vec3_cross(t_vec3 v, t_vec3 w);
t_vec3			vec3_scale(t_vec3 vec, float scale);
float			vec3_length(t_vec3 vec);
float			vec3_dot(t_vec3 v, t_vec3 w);
t_vec3			vec3_add(t_vec3 vec, t_vec3 vec1);
t_vec3			vec3_subtract(t_vec3 vec, t_vec3 vec1);
t_vec3			vec3_divide(t_vec3 vec, float scale);
t_vec3			vec3_multiply(t_vec3 vec, t_vec3 vec1);
t_vec3			vec3_square(t_vec3 vec);
float			degree_to_radians(float degrees);
float			radians_to_degrees(float radians);

#endif
