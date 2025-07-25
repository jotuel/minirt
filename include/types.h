#ifndef TYPES_H
# define TYPES_H
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>

/*
//emilia: maybe? These would be the base material types
// these would use the t_material data, but would have default
// settings, set by these categories.
// Default would have option for textures/images and normals
// metallic would have metal attributes
// and glass glass
// we can add more if wanted or create ready materials that players
// can play with // players? -j
typedef enum e_mat
{
	DEFAULT,
	METALLIC,
	GLASS,
	MAT1,
	MAT2,
}					t_mat;
*/

typedef enum e_var
{
    baba,
    bard,
    baoc,
    k2,
    k1,
    k0,
    h,
    t,
    y,
    ra
} t_var;

typedef enum e_type
{
    NONE,
    AMB,
	PLANE,
	SPH,
	CYL,
	LIGHT,
	CAM,
}					t_type;

typedef struct s_vec3
{
	float			x;
	float			y;
	float			z;
}					t_vec3;

typedef struct s_quat
{
    t_vec3          v;
    float           w;
}                   t_quat;

typedef t_vec3 t_point;

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

typedef struct s_cyl
{
	float	t0;
	float	t1;

}				t_cyl;

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
/// @param radius			= radius * 2
/// @param height
/// @param color
typedef struct s_cylinder
{
	t_point			pos;
	t_vec3			orientation;
	float			radius;
	float			height;
	t_color			color;
}					t_cylinder;

typedef struct s_sphere
{
	t_point			pos;
	float			radius;
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
	t_vec3			p00;
	t_vec3			u;
	t_vec3			v;
	t_vec3			w;
	t_vec3			vu;
	t_vec3			vv;
	t_vec3			vul;
	t_vec3			pixel_delta_u;
	t_vec3			pixel_delta_v;
	int				width;
	int				height;
	int				samplesperpixel;
	float			aspectratio;
}					t_camera;

typedef struct s_lightsource
{
	t_point			pos;
	float			intensity;
	t_color			color;
}					t_light;

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

typedef union u_object
{
	t_plane			plane;
	t_sphere		sphere;
	t_cylinder		cylinder;
}                   t_object;

// for tracking intersections, cast ray into the scene and get
// handful of intersections that return the intersections value (t)
// and object that was intersected

/// @brief return the intersections value (t) & object that was intersected
/// @param t float where hit happened
/// @param type t_type object type
/// @param point t_vec3 pos of object
/// @param color t_color color of object
typedef struct s_intersection
{
	float			t;
	t_type			type;
	t_vec3			point;
	t_color			color;
	t_object		*obj;

}					t_isect;

// node struct inside the content of linkedlist
typedef struct s_node
{
	int		data;
	struct s_node	*next;
	t_type	type;
	t_obj	*obj;

}					t_node;

// what is size in this content?
// float 19:8
typedef struct s_map
{
    t_camera        *camera;
    t_light         *light;
    t_ambient       *ambient;
	t_object   		*sp;
	t_object        *pl;
	t_object        *cy;
	unsigned int    nbr_sp;
	unsigned int    nbr_pl;
	unsigned int    nbr_cy;
	mlx_image_t     *img;
	mlx_t			*mlx;
	t_isect			*select;
}					t_map;

#endif
