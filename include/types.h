#ifndef TYPES_H
# define TYPES_H
# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>
# define MAX_OBJ 100

/*
//emilia: maybe? These would be the base material types
// these would use the t_material data, but would have default
// settings, set by these categories.
// Default would have option for textures/images and normals
// metallic would have metal attributes
// and glass glass
// we can add more if wanted or create ready materials that players
// can play with
typedef enum e_mat
{
	DEFAULT,
	METALLIC,
	GLASS,
	MAT1,
	MAT2,
}					t_mat;
*/

typedef enum e_type
{
    NONE,
    AMBIENT,
	PLANE,
	SPHERE,
	CYLINDER,
	LIGHT,
	CAMERA,
}					t_type;

// node struct inside the content of linkedlist
typedef struct s_node
{
	int		data;
	t_type	type;	

}					t_node;

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
	float			intensity;
	t_color			color;
}					t_ambient;

/*
// emilia: maybe something like this for material info?
typedef struct s_material
{
	t_color			color;
	float			roughness;
	t_color			normal;
	float			specularity; <-- maybe not needed, can be just defined as a set 0,5
	float			metallic; ?? <- or its own separate struct? maybe not

}					t_material;
*/

//emilia: for now, each object could have the t_color
// but if we end up creating materials then I would change the
// to_color to t_material and create a struct for that
typedef struct s_plane
{
	t_vec3			pos;
	t_vec3			orientation;
	t_color			color;
}					t_plane;

/// @param pos 				= a point on the axis
/// @param orientation		= axis direction
/// @param diameter			= radius * 2
/// @param height
/// @param color
typedef struct s_cylinder
{
	t_vec3			pos;
	t_vec3			orientation;
	float			diameter;
	float			height;
	float			min;
	float			max;
	bool			closed;
	bool			cap;
	t_color			color;
}					t_cylinder;

typedef struct s_sphere
{
	t_vec3			pos;
	float			diameter;
	t_color			color;
}					t_sphere;


/// @param fov								= field of view
/// @param vup								= view up
/// @param u, @param v, @param w			= Camera frame basis vectors
/// @param pixel_delta_u @param pixel_detal_v = gaps between pixels
typedef struct s_camera
{
	t_vec3			lookfrom;
	t_vec3			lookat;
	uint_fast8_t    fov;
	t_vec3			vup;
	t_vec3			pixel00_pos;
	t_vec3			u;
	t_vec3			v;
	t_vec3			w;
	t_vec3			pixel_delta_u;
	t_vec3			pixel_delta_v;
	int				width;
	int				height;
	int				samplesperpixel;
	float			aspectratio;
}					t_camera;

typedef struct s_lightsource
{
	t_vec3			pos;
	float			intensity;
	t_color			color;
}					t_light;

typedef t_vec3 t_point;
/// @param point1 = origin
/// @param point2 = direction
typedef struct s_ray
{
	t_point			origin;
	t_vec3			dir;
}					t_ray;

typedef struct s_obj
{
    t_ambient       ambiance;
	t_plane			plane;
	t_sphere		sphere;
	t_cylinder		cylinder;
	t_type			type;
	t_camera		cam;
	t_light			light;
}					t_obj;

// for tracking intersections, cast ray into the scene and get
// handful of intersections that return the intersections value (t)
// and object that was intersected
typedef struct s_intersection
{
	float			t;
	t_type			type;
}					t_intersection;

// what is size in this content?
// float 19:8
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
