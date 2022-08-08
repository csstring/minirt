/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:57:26 by schoe             #+#    #+#             */
/*   Updated: 2022/05/20 16:45:10 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "fdf.h"

void	ft_clear_map(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < 1440)
	{
		while (x < 2560)
		{
			my_mlx_pixel_put(&(map -> win), x, y, 0x00000000);
			x++;
		}
		x = 0;
		y++;
	}
}

void	make_mapval(int fd, t_map *map)
{
	char	*line;
	char	**split_line;
	int		y;
	int		x;
	int		i;

	i = 0;
	y = 0;
	while (y < map -> y)
	{
		x = 0;
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		split_line = ft_split(line, ' ');
		while (x < map -> x)
		{
			map -> val[y][x] = ft_atoi(split_line[x]);
			map -> color[i++] = map -> val[y][x];
			x++;
		}
		y++;
		free(line);
		ft_free_double((void **)split_line, map -> x);
	}
}

void	get_color(t_map *map)
{
	int	i;
	int	max;
	int	min;

	i = 0;
	max = int_max(map -> color, map);
	min = int_min(map -> color, map);
	while (i < map -> x * map -> y)
	{
		if (map -> color[i] <= (max - min) / 4)
			map -> color[i] = create_trgb(0, 0, 0, 255);
		else if (map -> color[i] <= (max - min) / 2)
			map -> color[i] = create_trgb(0, 0, 255, 0);
		else if (map -> color[i] <= (max - min) / 4 * 3)
			map -> color[i] = create_trgb(0, 255, 0, 0);
		else
			map -> color[i] = create_trgb(1, 150, 150, 150);
		i++;
	}
}

void	map_parsing(char *fdf, t_map *map)
{
	int	i;
	int	fd;

	i = 0;
	map_empty_check(fdf);
	map_error(fdf, map);
	fd = open(fdf, O_RDONLY);
	map -> val = (int **)malloc(sizeof(int *) * map -> y);
	map -> color = (int *)malloc(sizeof(int) * (map -> x * map -> y));
	if (!(map -> val) || !(map -> color))
		ft_error("Error : malloc fail");
	while (i < map -> y)
	{
		map -> val[i] = (int *)malloc(sizeof(int) * (map -> x));
		if (!(map -> val[i]))
			ft_error("Error : malloc fail");
		i++;
	}
	make_mapval(fd, map);
	get_color(map);
	close(fd);
	map -> deg_x = -0.615472907;
	map -> deg_y = PI / 4;
	map -> deg_z = 0;
}
