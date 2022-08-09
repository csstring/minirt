#include "sc_main.h"

int	distance_check(t_ray *ray,	double min_ans, double max_ans)
{
	double	root;

	root = min_ans;
	if (ray->rec.root_max < root || ray->rec.root_min > root)
	{
		root = max_ans;
		if (ray->rec.root_max < root || ray->rec.root_min > root)
			return (0);
	}
	ray->rec.root_max = root;
	ray->rec.root = root;
	return (1);
}

int	shadow_distance_check(t_ray *ray, double min_ans, double max_ans)
{
	double	root;

	root = min_ans;
	if (ray->rec.root_max < root || ray->rec.root_min > root)
	{
		root = max_ans;
		if (ray->rec.root_max < root || ray->rec.root_min > root)
			return (0);
	}
	return (1);
}

t_color3 get_ambient_color()
{
	return ((t_color3){0.15, 0.15, 0.15});
}

t_color3 get_diffuse_color(t_ray *ray)
{
	double	kd;

	ray->rec.light_dir = vunit(vminus(ray->light_origin, ray->rec.intersec_p));
	kd = vdot(ray->rec.light_dir, ray->rec.intersec_normal);
	if (kd < 0.0)
		kd = 0.0;
	return(vmult(ray->light_color, kd));
}

t_ray	shadow_check_ray(t_ray *ray)
{
	t_ray	temp;

	temp.origin = vplus(ray->rec.intersec_p, ray->rec.intersec_normal);
	temp.dir = vminus(ray->light_origin, ray->rec.intersec_p);
	temp.rec.root_min = 0;
	temp.rec.root_max = vlength(temp.dir);
	temp.dir = vunit(temp.dir);
	temp.rec.hit_flag = 1;
	return (temp);
}

int	shadow_check_sp(t_ray *ray, t_sphere sp)
{
	t_vec3  oc;
    double  a;
    double  b;
    double  c;
    double  discriminant;

    oc = vminus(ray->origin, sp.center);
    a = vdot(ray->dir, ray->dir);
    b = 2 * vdot(oc, ray->dir);
    c = vdot(oc, oc) - sp.radius * sp.radius;
    discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0.0)
		return (0);
	if (!shadow_distance_check(ray, (-b - sqrt(discriminant))/2/a, (-b + sqrt(discriminant))/2/a))
		return (0);
	return (1);
}

t_color3 get_specular_color(t_ray *ray)
{
	t_point3 reflect_light;
	double	spec;

	reflect_light = vminus(vmult(vmult(ray->rec.intersec_normal, \
	(vdot(ray->rec.light_dir, ray->rec.intersec_normal))), 2.0), ray->rec.light_dir);
	spec = vdot(reflect_light, vmult(ray->dir, -1.0));
	if (spec < 0.0)
		spec = 0.0;
	spec = powf(spec, 32);
	return (vmult(ray->light_color,spec));
}

int	hit_sphere(t_ray *ray, t_sphere sp, t_obj obj)
{
	t_vec3  oc;
    double  a;
    double  b;
    double  c;
    double  discriminant;
	t_ray	hit_check;
	int	i;

    oc = vminus(ray->origin, sp.center);
    a = vdot(ray->dir, ray->dir);
    b = 2 * vdot(oc, ray->dir);
    c = vdot(oc, oc) - sp.radius * sp.radius;
    discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (0);
	if (!distance_check(ray, (-b - sqrt(discriminant))/2/a, (-b + sqrt(discriminant))/2/a))
		return (0);
	ray->rec.hit_flag = 1;
	ray->rec.intersec_p = vplus(ray->origin,vmult(ray->dir, ray->rec.root));
	ray->rec.intersec_normal = vunit(vminus(ray->rec.intersec_p, sp.center));
	ray->rec.Ambient = get_ambient_color();
	i = 0;
	hit_check = shadow_check_ray(ray);
	while (i != obj.sphere_max_count)
	{
		if (shadow_check_sp(&hit_check, obj.sp[i++]))
		{
			ray->rec.fin_color = vplus(ray->rec.Ambient, (t_color3){0.0, 0.0, 0.0});
			return (1);
		}
	}
	ray->rec.Diffuse = get_diffuse_color(ray);
	ray->rec.Specular = get_specular_color(ray);
	ray->rec.fin_color = vmin(vplus(vplus(ray->rec.Ambient, ray->rec.Diffuse), \
						ray->rec.Specular), (t_color3){1,1,1});
	return (1);
}

t_sphere	sphere_init(t_point3 center, double radius)
{
	t_sphere sp;

	sp.center = center;
	sp.radius = radius;
	return (sp);
}