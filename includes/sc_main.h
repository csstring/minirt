/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sc_main.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:33:43 by schoe             #+#    #+#             */
/*   Updated: 2022/08/05 16:05:55 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SC_MAIN_H
# define SC_MAIN_H
# define PI			3.14159265
# define UP			126
# define DOWN		125
# define LEFT		123
# define RIGHT		124
# define ESC		53
# define KEYPRESS	2
# define ZOOM_IN	69
# define ZOOM_OUT	78
# define Q			12
# define W			13
# define E			14
# define A			0
# define S			1
# define D			2
# define ONE		18
# define TWO		19
# define THREE		20
# define FOUR		21

#include "vecdef.h"
#include "cam_view.h"
#include "ray.h"
#include "object.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	void	*mlx_win;
}	t_data;

typedef struct s_map
{
	t_data		win;
}	t_map;
//map
void	ft_clear_map(t_map *map);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	ft_init_win(t_map *map);

//color
int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
//key
void	ft_key_parallel(int keycode, t_map *map);
void	ft_key_deg(int keycode, t_map *map);
int		ft_key_press(int keycode, t_map *map);

#endif
