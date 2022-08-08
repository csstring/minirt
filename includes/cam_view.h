#ifndef CAM_VIEW_H
# define CAM_VIEW_H

#include "sc_main.h"

#define	WIDTH 1920
#define HEIGT 1080

typedef struct s_camera
{
	t_point3	origin;
	t_vec3		dir;
	t_vec3		r_normal;
	t_vec3		up_normal;
	t_point3	leftdown_coner;
	double		fov;
	double		focal_len;
}	t_cam;

t_cam	cam_init(t_point3 origin, t_vec3 dir);
void	print_vec3(t_vec3	temp);
#endif