/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:25:26 by schoe             #+#    #+#             */
/*   Updated: 2022/08/04 18:26:47 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include <fcntl.h>

void	ft_error(char *str)
{
	ft_printf("%s\n", str);
	exit(1);
}

void	arg_error(int k, char **input)
{
	char	**str;
	int		i;
	int		count;

	count = 0;
	i = 0;
	if (k != 2)
		ft_error("Error : The number of input is wrong");
	while (input[1][i])
		i++;
	if (input[1][--i] == '.')
		ft_error("Error : wrong argc form");
	i = 0;
	if (input[1][i] == '.')
		ft_error("Error : is hidden file");
	str = ft_split(input[1], '.');
	if (str != NULL)
		while (str[i])
			i++;
	if (i != 2)
		ft_error("Error : wrong argc form");
	if (ft_strncmp(str[1], "fdf", 4) != 0)
		ft_error("Error : wrong argc form");
	ft_free_double((void **)str, i);
}

void	map_empty_check(char *fdf)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(fdf, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		i++;
		if (line == NULL)
		{
			if (i == 1)
				ft_error("Error : empty file");
			break ;
		}
		free(line);
	}
	close(fd);
}

void	map_error(char *fdf, t_map *map)
{
	char	*line;
	char	**split_line;
	int		y;
	int		fd;

	y = 0;
	fd = open(fdf, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		y++;
		if (line == NULL)
			break ;
		split_line = ft_split(line, ' ');
		if (map -> x == 0)
			map -> x = ft_map_len(split_line);
		if (map -> x != ft_map_len(split_line))
			ft_error("Error : map is not rectangle");
		free(line);
		ft_free_double((void **)split_line, map -> x);
	}
	close(fd);
	map -> y = y;
}
