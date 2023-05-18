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

static t_point	ft_isometric(t_point point, double angle, int interspace, int height);

/* à protéger quand il n'y a qu'un point, qu'une ligne, ... */
void	ft_print_map(t_map_data *map_data, t_img_data *s_img, int interspace, int height)
{
	int				i;
	int				row;
	int				column;

	row = map_data->total_row;
	column = map_data->total_column;
	i = 0;
	while (row-- > 0)
	{
		while (column-- > 1)
		{
			ft_draw_line(s_img, ft_isometric((map_data->map)[i], 0.523599, interspace, height), ft_isometric((map_data->map)[i + 1], 0.523599, interspace, height));
			++i;
		}
		++i;
		column = map_data->total_column;
	}
	row = map_data->total_row;
	column = map_data->total_column;
	i = 0;
	while (column-- > 0)
	{
		while (row-- > 1)
		{
			ft_draw_line(s_img, ft_isometric((map_data->map)[i], 0.523599, interspace, height), ft_isometric((map_data->map)[i + map_data->total_column], 0.523599, interspace, height));
			i += map_data->total_column;
		}
		i -= (map_data->total_row - 1) * map_data->total_column + 1;
		row = map_data->total_row;
	}
}

t_point	ft_isometric(t_point point, double angle, int interspace, int height)
{
	// point->x = point->x + cos(angle) * point->z - cos(angle) * point->y;
	// point->y = -(point->y) * sin(angle) - point->z * sin(angle);

	int previous_x;
    int previous_y;

    previous_x = point.x * interspace;
    previous_y = point.y * interspace;
    point.x = (previous_x - previous_y) * cos(angle);
    point.y = -(point.z) * height + (previous_x + previous_y) * sin(angle);
	return (point);
}
