/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_distance.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:20:23 by schoe             #+#    #+#             */
/*   Updated: 2022/05/17 20:48:59 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	double_max(double *arr, t_map *map)
{
	int		i;
	double	temp;
	double	max;

	i = 0;
	if (map -> x * map -> y == 1)
		return (arr[i]);
	max = arr[i];
	while (i < map -> x * map -> y)
	{
		temp = arr[i];
		if (temp > max)
			max = temp;
		i++;
	}
	return (max);
}

double	double_min(double *arr, t_map *map)
{
	int		i;
	double	temp;
	double	min;

	i = 0;
	if (map ->x * map -> y == 1)
		return (arr[i]);
	min = arr[i];
	while (i < map -> x * map -> y)
	{
		temp = arr[i];
		if (temp < min)
			min = temp;
		i++;
	}
	return (min);
}

void	get_distance(t_map *map)
{
	double	x_max;
	double	x_min;
	double	y_max;
	double	y_min;
	int		i;

	i = 0;
	x_max = double_max(map -> rot.x, map);
	y_max = double_max(map -> rot.y, map);
	x_min = double_min(map -> rot.x, map);
	y_min = double_min(map -> rot.y, map);
	while (i < map -> x * map -> y)
	{
		map -> rot.x[i] = (map -> rot.x[i] - x_min) * (map -> distance);
		map -> rot.y[i] = (map -> rot.y[i] - y_min) * (map -> distance);
		i++;
	}
	i = 0;
	while (i < map -> x * map -> y)
	{
		map -> rot.x[i] += 1000 + map -> move_x;
		map -> rot.y[i] += 20 + map -> move_y;
		i++;
	}
}
