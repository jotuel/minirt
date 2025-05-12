#ifndef TYPES_H
# define TYPES_H
# include <stddef.h>
# include <stdint.h>
# define MAX_OBJ 100

typedef enum e_shape
{
    NONE,
    AMBIENT,
	PLANE,
	SPHERE,
	CYLINDER,
	LIGHT,
	CAMERA,
}					t_shape;

typedef struct s_vec3
{
	float			x;
	float			y;
	float			z;
}					t_vec3;

typedef struct s_color
{
	uint_fast8_t	r;
	uint_fast8_t	g;
	uint_fast8_t	b;
}					t_color;

typedef struct s_ambient
{
	float			range;
	t_color			color;
}					t_ambient;

typedef struct s_plane
{
	t_vec3			pos;
	t_vec3			orientation;
	t_color			color;
}					t_plane;

typedef struct s_cylinder
{
	t_vec3			pos;
	t_vec3			orientation;
	float			diameter;
	float			height;
	t_color			color;
}					t_cylinder;

typedef struct s_sphere
{
	t_vec3			pos;
	float			diameter;
	t_color			color;
}					t_sphere;

typedef struct s_camera
{
	t_vec3			pos;
	t_vec3			orientation;
	uint_fast8_t    fov;
}					t_camera;

typedef struct s_lightsource
{
	t_vec3			pos;
	float			range;
	t_color			color;
}					t_light;

typedef struct s_obj
{
    t_ambient       ambiance;
	t_plane			plane;
	t_sphere		sphere;
	t_cylinder		cylinder;
	t_shape			shape;
	t_camera		cam;
	t_light			light;
}					t_obj;

typedef struct s_map
{
	t_obj			*obj[MAX_OBJ];
	size_t			nbr;
	size_t			dimensions[3];
	size_t          size;
	size_t          capacity;
	void			*space;
}					t_map;

#endif
