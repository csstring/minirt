/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:54:43 by schoe             #+#    #+#             */
/*   Updated: 2022/05/20 16:45:27 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <unistd.h>

int	int_max(int *arr, t_map *map)
{
	int	i;
	int	temp;
	int	max;

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

int	int_min(int *arr, t_map *map)
{
	int	i;
	int	temp;
	int	min;

	i = 0;
	if (map -> x * map -> y == 1)
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

int	ft_map_len(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		ft_error("Error : non-existent map");
	while (str[i])
		i++;
	return (i);
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
