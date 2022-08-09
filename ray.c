#include "sc_main.h"

t_ray	get_viewport_ray(t_cam cam, double x, double y)
{
	t_ray	ray;
	t_vec3	w;
	t_vec3	h;
	t_point3	view_vec;

	ray.origin = cam.origin;
	w = vmult(cam.r_normal, x);
	h = vmult(cam.up_normal, y);
	view_vec = vplus(cam.leftdown_coner, w);
	view_vec = vplus(view_vec, h);
	ray.dir = vunit(vminus(view_vec, ray.origin));
	ray.rec.root_min = 0;
	ray.rec.root_max = 10000;
	ray.rec.hit_flag = 0;
	ray.light_color = (t_color3){0.5, 0.5, 0.5};
	ray.light_origin = (t_point3){-560 + 1 * 1000 , -3000, -1150};
	return (ray);
}