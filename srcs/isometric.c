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

t_point	ft_isometric(t_point point, t_isometric_data *s_isometric_data);
double	ft_rad(int degree);

/* à protéger quand il n'y a qu'un point, qu'une ligne, ... */
void	ft_print_map(t_fdf *s_fdf)
{
	int				i;
	int				row;
	int				column;

	row = s_fdf->map_data.total_row;
	column = s_fdf->map_data.total_column;
	i = 0;
	while (row-- > 0)
	{
		while (column-- > 1)
		{
			ft_draw_line(&(s_fdf->mlx_data.s_img), ft_isometric((s_fdf->map_data.map)[i], &(s_fdf->s_isometric_data)), ft_isometric((s_fdf->map_data.map)[i + 1], &(s_fdf->s_isometric_data)));
			++i;
		}
		++i;
		column = s_fdf->map_data.total_column;
	}
	row = s_fdf->map_data.total_row;
	column = s_fdf->map_data.total_column;
	i = 0;
	while (column-- > 0)
	{
		while (row-- > 1)
		{
			ft_draw_line(&(s_fdf->mlx_data.s_img), ft_isometric((s_fdf->map_data.map)[i], &(s_fdf->s_isometric_data)), ft_isometric((s_fdf->map_data.map)[i + s_fdf->map_data.total_column], &(s_fdf->s_isometric_data)));
			i += s_fdf->map_data.total_column;
		}
		i = s_fdf->map_data.total_column - column;
		row = s_fdf->map_data.total_row;
	}
}

double	ft_rad(int degree)
{
	return (degree * (M_PI / 180.0));
}

t_point	ft_isometric(t_point point, t_isometric_data *s_isometric_data)
{
	// point->x = point->x + cos(angle) * point->z - cos(angle) * point->y;
	// point->y = -(point->y) * sin(angle) - point->z * sin(angle);
	 
	int previous_x;
    int previous_y;

    previous_x = point.x * s_isometric_data->interspace;
    previous_y = point.y * s_isometric_data->interspace;
    point.x = s_isometric_data->origin_x + s_isometric_data->move_x + (previous_x - previous_y) * cos(s_isometric_data->angle);
    point.y = s_isometric_data->origin_y + s_isometric_data->move_y + -(point.z) * s_isometric_data->height + (previous_x + previous_y) * sin(s_isometric_data->angle);
	return (point);
}
