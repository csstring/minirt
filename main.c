/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:51:08 by schoe             #+#    #+#             */
/*   Updated: 2022/08/09 17:20:31 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx/mlx.h"
#include "sc_main.h"

int	ft_key_press(int keycode, t_map *map)
{
	if (keycode == ESC)
	{
		mlx_destroy_image(map -> win.mlx, map -> win.img);
		mlx_destroy_window(map -> win.mlx, map -> win.mlx_win);
		exit(0);
	}
	return (0);
}

void	print_vec3(t_vec3	temp)
{
	printf("x : %f y : %f z: %f\n", temp.x, temp.y, temp.z);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (y < 0)
		while (y < 0)
			y += 1440;
	else if (y > 1439)
		while (y > 1439)
			y -= 1439;
	if (x < 0)
		while (x < 0)
			x += 2560;
	else if (x > 2559)
		while (x > 2559)
			x -= 2559;
	dst = data -> addr + (y * data -> line_length + x * \
			(data -> bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_init_win(t_map *map)
{
	int	y;
	int	i;

	y = 0;
	i = 0;
	map -> win.mlx = mlx_init();
	map -> win.mlx_win = mlx_new_window(map -> win.mlx, 2560, 1440, "RTv0.001");
	map -> win.img = mlx_new_image(map -> win.mlx, 2560, 1440);
	map -> win.addr = mlx_get_data_addr(map -> win.img, \
			&(map -> win.bits_per_pixel), &(map -> win.line_length), \
			&(map -> win.endian));
}

t_color3    ray_color(double r)
{
    double  t;

    t = 0.5 * (r + 1.0);
    return (vplus(vmult(color3(1, 1, 1), 1.0 - t), vmult(color3(0.5, 0.7, 1.0), t)));
}

void	write_color_img(t_cam cam, t_map *map, t_obj obj, int i)
{
	int	x;
	int	y;
	t_color3	color;
	t_ray	ray;

	y = 0;
	while (y < HEIGT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = get_viewport_ray(cam, x, y);
			i = 0;
			while (i != obj.sphere_max_count)
			{
				if (i == obj.sphere_max_count - 1 && hit_sphere(&ray, obj.sp[i], obj))
					color = vmin(vplus((t_color3){0.0 ,0, 0.8}, ray.rec.fin_color), (t_color3){1,1,1});
				else if (i % 2 == 1 && hit_sphere(&ray, obj.sp[i], obj))
					color = vmin(vplus(ray_color(0.9) , ray.rec.fin_color), (t_color3){1,1,1});
				else if (i % 2 == 0 && hit_sphere(&ray, obj.sp[i], obj))
					color = vmin(vplus((t_color3){0.4 ,0, 0}, ray.rec.fin_color), (t_color3){1,1,1});
				i++;
			}
			if (!ray.rec.hit_flag)
				color = ray_color(ray.dir.y);
			my_mlx_pixel_put(&map->win, x, y, \
			create_trgb(0, 255.99*color.x, 255.99*color.y, 255.99*color.z));
			x++;
		}
		y++;
	}
}

void	make_sphere(t_obj *obj)
{
	t_sphere *sp;
	int	i;
	int	rand_per;

	rand_per = 50;
	i = 0;
	sp = (t_sphere *)malloc(sizeof(t_sphere) * rand_per);
	while (i < rand_per)
	{
		if (rand() % 2)
			sp[i] = sphere_init((t_point3){-3000 + rand() % rand_per * 150 , 400 - rand() % rand_per * 50, -3150 }, \
					200 - rand() % rand_per * 2);
		else
			sp[i] = sphere_init((t_point3){-3000 + rand() % rand_per * 150 , -100 + rand() % rand_per * 50, -3150 }, \
					100 + rand() % rand_per * 2);
		i++;
	}
	sp[i++] = sphere_init((t_point3){1400 , 14200, -3050}, 12000);
	obj->sp	= sp;
	obj->sphere_max_count = i;
}

int	main(void)
{
	t_map	map;
	t_cam	cam;
	t_obj	obj;
	int	i;

	i = 0;
	ft_memset(&map, 0, sizeof(map));
	ft_init_win(&map);
	cam = cam_init((t_point3){0, 0, 0}, (t_vec3){0,0,-1});
	make_sphere(&obj);
	write_color_img(cam, &map, obj, i);
	mlx_put_image_to_window(map.win.mlx, map.win.mlx_win, map.win.img, 0, 0);
	mlx_hook(map.win.mlx_win, KEYPRESS, 0, ft_key_press, &map);
	mlx_loop(map.win.mlx);
	return (0);
}
