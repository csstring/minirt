#ifndef OBJECT_H
# define OBJECT_H

#include "sc_main.h"

typedef struct	s_sphere
{
	double	radius;
	t_point3	center;
}	t_sphere;

typedef struct s_obj
{
	t_sphere *sp;
	int		sphere_max_count;
}	t_obj;

int	hit_sphere(t_ray *ray, t_sphere sp, t_obj obj);
t_sphere	sphere_init(t_point3 center, double radius);

#endif