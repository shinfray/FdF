/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:50:59 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/26 04:06:51 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			ft_print_map(t_fdf *s_fdf);
void			ft_reprint_image(t_fdf *s_fdf);
static void		ft_print_rows(t_fdf *s_fdf, t_line *s_line);
static void		ft_print_colums(t_fdf *s_fdf, t_line *s_line);
static t_point	ft_isometric(t_point point, t_isometric_data *s_isometric_data);

/* à protéger quand il n'y a qu'un point, qu'une ligne, ... */
void	ft_print_map(t_fdf *s_fdf)
{
	t_line	s_line;
	t_point	s_point;

	if (s_fdf->s_map_data.total_size > 1)
	{
		ft_print_rows(s_fdf, &s_line);
		ft_print_colums(s_fdf, &s_line);
	}
	else
	{
		s_point = ft_isometric(*(s_fdf->s_map_data.s_map), \
			&(s_fdf->s_isometric_data));
		ft_pixel_put(&(s_fdf->s_mlx_data.s_img), &s_point);
	}
	ft_refresh_interface(s_fdf);
}

void	ft_reprint_image(t_fdf *s_fdf)
{
	void		*backup;

	backup = s_fdf->s_mlx_data.s_img.img;
	s_fdf->s_mlx_data.s_img.img = mlx_new_image(s_fdf->s_mlx_data.mlx_ptr, \
			WINDOW_WIDTH, WINDOW_HEIGHT);
	if (s_fdf->s_mlx_data.s_img.img == NULL)
	{
		s_fdf->s_mlx_data.s_img.img = backup;
		s_fdf->exit_status = EXIT_FAILURE;
		ft_clean_quit(s_fdf);
	}
	s_fdf->s_mlx_data.s_img.addr = \
			mlx_get_data_addr(s_fdf->s_mlx_data.s_img.img, \
			&(s_fdf->s_mlx_data.s_img.bpp), \
			&(s_fdf->s_mlx_data.s_img.line_len), \
			&(s_fdf->s_mlx_data.s_img.endian));
	ft_print_map(s_fdf);
	mlx_destroy_image(s_fdf->s_mlx_data.mlx_ptr, backup);
}

static void	ft_print_rows(t_fdf *s_fdf, t_line *s_line)
{
	int				i;
	int				row;
	int				column;

	i = 0;
	row = s_fdf->s_map_data.total_row;
	column = s_fdf->s_map_data.total_column;
	while (row-- > 0)
	{
		while (column-- > 1)
		{
			s_line->start = ft_isometric((s_fdf->s_map_data.s_map)[i], \
				&(s_fdf->s_isometric_data));
			s_line->end = ft_isometric((s_fdf->s_map_data.s_map)[i + 1], \
				&(s_fdf->s_isometric_data));
			ft_draw_line(&(s_fdf->s_mlx_data.s_img), s_line);
			++i;
		}
		++i;
		column = s_fdf->s_map_data.total_column;
	}
}

static void	ft_print_colums(t_fdf *s_fdf, t_line *s_line)
{
	int				i;
	int				row;
	int				column;

	i = 0;
	row = s_fdf->s_map_data.total_row;
	column = s_fdf->s_map_data.total_column;
	while (column-- > 0)
	{
		while (row-- > 1)
		{
			s_line->start = ft_isometric((s_fdf->s_map_data.s_map)[i], \
				&(s_fdf->s_isometric_data));
			s_line->end = ft_isometric((s_fdf->s_map_data.s_map)[i \
				+ s_fdf->s_map_data.total_column], &(s_fdf->s_isometric_data));
			ft_draw_line(&(s_fdf->s_mlx_data.s_img), s_line);
			i += s_fdf->s_map_data.total_column;
		}
		i = s_fdf->s_map_data.total_column - column;
		row = s_fdf->s_map_data.total_row;
	}
}

static t_point	ft_isometric(t_point point, t_isometric_data *s_isometric_data)
{
	const double	alpha = s_isometric_data->angle_x;
	const double	beta = s_isometric_data->angle_y;
	const double	gamma = s_isometric_data->angle_z;
	const int		previous_x = point.x * s_isometric_data->interspace;
	const int		previous_y = point.y * s_isometric_data->interspace;
	const int		previous_z = point.z * (s_isometric_data->height);

	point.x = previous_x * cos(beta) * cos(gamma) \
			+ previous_y * (sin(alpha) * sin(beta) * cos(gamma) - cos(alpha) * sin(gamma)) \
			+ previous_z * (cos(alpha) * sin(beta) * cos(gamma) + sin(alpha) * sin(gamma));
	point.y = previous_x * cos(beta) * sin(gamma) \
			+ previous_y * (sin(alpha) * sin(beta) * sin(gamma) + cos(alpha) * cos(gamma)) \
			+ previous_z * (cos(alpha) * sin(beta) * sin(gamma) - sin(alpha) * cos(gamma));
	point.z = previous_x * -sin(beta) \
			+ previous_y * sin(alpha) * cos(beta) \
			+ previous_z * cos(alpha) * cos(beta);
	point.x += s_isometric_data->move_x;
	point.y = point.y + s_isometric_data->move_y;
	return (point);
}
