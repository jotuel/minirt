#ifndef DECLARE_H
#define DECLARE_H
#include "../MLX42/include/MLX42/MLX42.h"
#include "types.h"
#include <stdbool.h>

void ft_error(void *mem);

/* CASTING RAYS */
float hit_sphere(t_point center, float radius, t_ray r);
uint_fast32_t color_ray(t_ray r);
float intersect_plane(t_vec3 center, t_vec3 rot, t_ray r);

/* SET & GET FUNCTIONS */
float vec3_get_z(t_vec3 vec);
float vec3_get_x(t_vec3 vec);
float vec3_get_y(t_vec3 vec);
void vec3_set_x(t_vec3 *vec, float x);
void vec3_set_y(t_vec3 *vec, float y);
void vec3_set_z(t_vec3 *vec, float z);
void set_vec3(char **vec3, t_vec3 *vec);
void set_colors(char **colors, t_color *color);
void set_red(t_color *color, uint8_t colour);
void set_green(t_color *color, uint8_t colour);
void set_blue(t_color *color, uint8_t colour);
uint_fast32_t get_color(t_color color);
uint_fast32_t pixel_color(void);
void ambient(char *line, t_map *rt, t_ambient amb);
void camera(char *line, t_map *rt, t_camera cam);
void initialize_camera(t_camera *camera, mlx_image_t *img);
void cylinder(char *line, t_map *rt, t_cylinder cy);
void plane(char *line, t_map *rt, t_plane pl);
void sphere(char *line, t_map *rt, t_sphere sp);
void light(char *line, t_map *rt, t_light light);

/* MAP PARSING */
void parse_file(char *filename, t_map *minirt);
char **split_and_check(char *input, char by, int fields, void *mem);
void free_split(char **split);

/* MATH */
float lerp(float s, float e, float f);
uint_fast8_t color_lerp(float f);
float to_degrees(float radians);
float to_radians(float degrees);

/* VECTOR MATH */
uint_fast32_t vec3_lerp(t_vec3 v);
t_vec3 vec3_unit(t_vec3 v);
t_vec3 vec3_neg(t_vec3 vec);
t_vec3 vec3_cross(t_vec3 v, t_vec3 w);
t_vec3 vec3_scale(t_vec3 vec, float scale);
float vec3_length(t_vec3 vec);
float vec3_dot(t_vec3 v, t_vec3 w);
t_vec3 vec3_add(t_vec3 vec, t_vec3 vec1);
t_vec3 vec3_subtract(t_vec3 vec, t_vec3 vec1);
t_vec3 vec3_multiply(t_vec3 vec, t_vec3 vec1);
t_vec3 vec3_square(t_vec3 vec);
t_vec3 reflection(t_vec3 vec, t_vec3 n);
t_vec3 vec3_cross(t_vec3 v, t_vec3 w);
t_vec3 vec3_scale(t_vec3 vec, float scale);
float vec3_length(t_vec3 vec);
float vec3_dot(t_vec3 v, t_vec3 w);
t_vec3 vec3_add(t_vec3 vec, t_vec3 vec1);
t_vec3 vec3_subtract(t_vec3 vec, t_vec3 vec1);
t_vec3 vec3_divide(t_vec3 vec, float scale);
t_vec3 vec3_multiply(t_vec3 vec, t_vec3 vec1);
t_vec3 vec3_square(t_vec3 vec);
float degree_to_radians(float degrees);
float radians_to_degrees(float radians);

#endif
