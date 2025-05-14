#ifndef DECLARE_H
# define DECLARE_H
# include "types.h"

void ft_error(void *mem);

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
void ambient(char *line, t_map *rt, t_ambient amb);
void camera(char *line, t_map *rt, t_camera cam);
void cylinder(char *line, t_map *rt, t_cylinder cy);
void plane(char *line, t_map *rt, t_plane pl);
void sphere(char *line, t_map *rt, t_sphere sp);
void light(char *line, t_map *rt, t_light light);

/* MAP PARSING */
t_map parse_file(char *filename, t_map minirt);
char **split_and_check(char *input, char by, int fields, void *mem);
void free_split(char **split);

/* VECTOR MATH */
t_vec3 vec3_cross(t_vec3 v, t_vec3 w);
t_vec3 vec3_scale(t_vec3 vec, float scale);
float vec3_length(t_vec3 vec);
float vec3_dot(t_vec3 v, t_vec3 w);
t_vec3 vec3_add(t_vec3 vec, t_vec3 vec1);
t_vec3 vec3_subtract(t_vec3 vec, t_vec3 vec1);
t_vec3 vec3_multiply(t_vec3 vec, t_vec3 vec1);
t_vec3 vec3_square(t_vec3 vec);


#endif
