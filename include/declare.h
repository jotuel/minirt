#ifndef DECLARE_H
# define DECLARE_H
# include "types.h"

void ft_error(void *mem);
char **split_and_check(char *input, char by, int fields, void *mem);
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
t_map parse_file(char *filename, t_map minirt);


#endif
