/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 17:43:47 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/06 10:52:56by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_isometric(t_point *point, float angle);

/* à protéger quand il n'y a qu'un point, qu'une ligne, ... */
void	ft_print_map(t_map_data *map_data, t_img_data *s_img)
{
	t_point			point_1;
	t_point			point_2;
	t_coordinates	s_coordinates;
	int				i;
	int				row;
	int				column;

	row = map_data->total_row;
	column = map_data->total_column;
	i = 0;
	while (row-- > 0)
	{
		while (i + 1 < map_data->total_column)
		{
			point_1 = (map_data->map)[i];
			point_2 = (map_data->map)[i + 1];
			ft_isometric(&point_1, 0.523599);
			ft_isometric(&point_2, 0.523599);
			s_coordinates.x1 = point_1.x;
			s_coordinates.y1 = point_1.y;
			s_coordinates.x2 = point_2.x;
			s_coordinates.y2 = point_2.y;
			s_coordinates.color = 0x34B6A4;
			ft_draw_line(s_img, s_coordinates);
			++i;
		}
		++i;
	}
	i = 0;
	while (column-- > 0)
	{
		while (i + map_data->total_column < map_data->total_column * map_data->total_row)
		{
			point_1 = (map_data->map)[i];
			point_2 = (map_data->map)[i + map_data->total_column];
			ft_isometric(&point_1, 0.523599);
			ft_isometric(&point_2, 0.523599);
			s_coordinates.x1 = point_1.x;
			s_coordinates.y1 = point_1.y;
			s_coordinates.x2 = point_2.x;
			s_coordinates.y2 = point_2.y;
			s_coordinates.color = 0x34B6A4;
			ft_draw_line(s_img, s_coordinates);
			i += map_data->total_column;
		}
		i -= (map_data->total_row - 1) * map_data->total_column + 1;
	}
}

void	ft_isometric(t_point *point, float angle)
{
	point->x = point->x + cos(angle) * point->z - cos(angle) * point->y;
	point->y = -(point->y) * sin(angle) - point->z * sin(angle);
}
