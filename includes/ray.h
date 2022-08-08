#ifndef RAY_H
# define RAY_H

#include "sc_main.h"

typedef struct s_hit_recode
{
	t_point3	intersec_p;
	t_vec3		intersec_normal;
	double		root_min;
	double		root_max;
	double		root;
	int			in_out_check;
	int			hit_flag;
	t_point3	light_dir;
	t_color3	Ambient;
	t_color3	Diffuse;
	t_color3	Specular;
	t_color3	fin_color;
}	t_rec;

typedef struct s_ray
{
	t_point3	origin;
	t_vec3		dir;
	t_rec		rec;
	t_point3	light_origin;
	t_color3	light_color;
}	t_ray;

t_ray	get_viewport_ray(t_cam cam, double x, double y);

#endif
