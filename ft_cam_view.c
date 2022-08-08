#include "sc_main.h"

t_cam	cam_init(t_point3 origin, t_vec3 dir)
{
	t_cam	cam;
	t_vec3	vec_y;
	t_vec3	vec_z;
	t_point3	temp_coner;

	vec_y = (t_vec3){0, 1, 0};
	vec_z = (t_vec3){0, 0, -1};
	cam.origin = origin;
	cam.dir = dir;
	if (vlength(vcross(cam.dir, vec_y)))
		cam.r_normal = vunit(vcross(cam.dir, vec_y));
	else
		cam.r_normal = vunit(vcross(cam.dir, vec_z));
	cam.up_normal = vunit(vcross(cam.r_normal, cam.dir));
	cam.fov = 90.0000 / 180.00000 * M_PI;
	cam.focal_len = (double)WIDTH / 2 / tan(cam.fov / 2);
	printf("tan : %f\n", tan(cam.fov / 2));
	printf("focal_len : %f\n", cam.focal_len);
	temp_coner = vplus(cam.origin, vmult(cam.dir, cam.focal_len));
	temp_coner = vplus(temp_coner, vmult(cam.r_normal, -(double)((WIDTH - 1) / 2)));
	cam.leftdown_coner = vplus(temp_coner, vmult(cam.up_normal, -(double)((HEIGT - 1) / 2)));
	print_vec3(cam.r_normal);
	print_vec3(cam.up_normal);
	print_vec3(cam.leftdown_coner);
	return (cam);
}
