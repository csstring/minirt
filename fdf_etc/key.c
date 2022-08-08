/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:23:10 by schoe             #+#    #+#             */
/*   Updated: 2022/08/05 16:00:25 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sc_main.h"
#include "./minilibx/mlx.h"

void	ft_key_parallel(int keycode, t_map *map)
{
	if (keycode == ONE)
	{
		map -> deg_x = -PI / 2;
		map -> deg_y = 0;
		map -> deg_z = 0;
	}
	else if (keycode == TWO)
	{
		map -> deg_x = 0;
		map -> deg_y = 0;
		map -> deg_z = 0;
	}
	else if (keycode == THREE)
	{
		map -> deg_x = 0;
		map -> deg_y = -PI / 2;
		map -> deg_z = 0;
	}
	else if (keycode == FOUR)
	{
		map -> deg_x = -0.615472907;
		map -> deg_y = PI / 4;
		map -> deg_z = 0;
	}
}

void	ft_key_deg(int keycode, t_map *map)
{
	if (keycode == W)
		map -> deg_x += PI / 30;
	else if (keycode == S)
		map -> deg_x -= PI / 30;
	else if (keycode == A)
		map -> deg_z -= PI / 30;
	else if (keycode == D)
		map -> deg_z += PI / 30;
	else if (keycode == Q)
		map -> deg_y += PI / 30;
	else if (keycode == E)
		map -> deg_y -= PI / 30;
}

void	ft_key_move(int keycode, t_map *map)
{	
	if (keycode == LEFT)
		map -> move_x -= 30;
	else if (keycode == RIGHT)
		map -> move_x += 30;
	else if (keycode == UP)
		map -> move_y -= 30;
	else if (keycode == DOWN)
		map -> move_y += 30;
}

int	ft_key_press(int keycode, t_map *map)
{
	if (keycode == ESC)
	{
		mlx_destroy_image(map -> win.mlx, map -> win.img);
		mlx_destroy_window(map -> win.mlx, map -> win.mlx_win);
		exit(0);
	}
	else if (keycode == ZOOM_IN && ((double_max(map -> rot.y, \
			map) - double_min(map -> rot.y, map) < 1440 * 0.8) || \
			(double_max(map -> rot.x, map) - double_min(map -> rot.x, map) \
			< 2560 * 0.8)))
		map -> distance += 0.3;
	else if (keycode == ZOOM_OUT && map -> distance - 0.2 > 1)
		map -> distance -= 0.2;
	else
	{
		ft_key_move(keycode, map);
		ft_key_deg(keycode, map);
		ft_key_parallel(keycode, map);
	}
	main_loop(map);
	return (0);
}
