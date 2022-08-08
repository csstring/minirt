/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iso.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:02:48 by schoe             #+#    #+#             */
/*   Updated: 2022/05/20 16:39:03 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>

void	ft_rot_x(t_map *map, int i)
{
	double	rad;
	double	x;
	double	y;
	double	z;

	x = map -> rot.x[i];
	y = map -> rot.y[i];
	z = map -> rot.z[i];
	rad = map -> deg_x;
	map -> rot.x[i] = x;
	map -> rot.y[i] = cos(rad) * y - sin(rad) * z;
	map -> rot.z[i] = sin(rad) * y + cos(rad) * z;
}

void	ft_rot_y(t_map *map, int i)
{
	double	rad;
	double	x;
	double	y;
	double	z;

	x = map -> rot.x[i];
	y = map -> rot.y[i];
	z = map -> rot.z[i];
	rad = map -> deg_y;
	map -> rot.x[i] = cos(rad) * x + sin(rad) * z;
	map -> rot.y[i] = y;
	map -> rot.z[i] = -sin(rad) * x + cos(rad) * z;
}

void	ft_rot_z(t_map *map, int i)
{
	double	rad;
	double	x;
	double	y;
	double	z;

	x = map -> rot.x[i];
	y = map -> rot.y[i];
	z = map -> rot.z[i];
	rad = map -> deg_z;
	map -> rot.x[i] = cos(rad) * x - sin(rad) * y;
	map -> rot.y[i] = sin(rad) * x + cos(rad) * y;
	map -> rot.z[i] = z;
}

void	ft_rotate(t_map *map)
{
	int	y;
	int	i;
	int	x;

	y = 0;
	i = 0;
	map -> rot.x = (double *)malloc(sizeof(double) * (map -> x * map -> y));
	map -> rot.y = (double *)malloc(sizeof(double) * (map -> x * map -> y));
	map -> rot.z = (double *)malloc(sizeof(double) * (map -> x * map -> y));
	while (y < map -> y)
	{
		x = 0;
		while (x < map -> x)
		{
			map -> rot.x[i] = x;
			map -> rot.y[i] = cos(PI / 2) * y - sin(PI / 2) * map -> val[y][x];
			map -> rot.z[i] = sin(PI / 2) * y + cos(PI / 2) * map -> val[y][x];
			ft_rot_y(map, i);
			ft_rot_x(map, i);
			ft_rot_z(map, i);
			x++;
			i++;
		}
		y++;
	}
}
