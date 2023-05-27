/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 02:52:59 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/27 02:53:00 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			ft_print_map(t_fdf *s_fdf);
void			ft_reprint_image(t_fdf *s_fdf);
static void		ft_print_rows(t_fdf *s_fdf, t_line *s_line);
static void		ft_print_colums(t_fdf *s_fdf, t_line *s_line);

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
			&(s_fdf->s_isometric));
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
				&(s_fdf->s_isometric));
			s_line->end = ft_isometric((s_fdf->s_map_data.s_map)[i + 1], \
				&(s_fdf->s_isometric));
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
				&(s_fdf->s_isometric));
			s_line->end = ft_isometric((s_fdf->s_map_data.s_map)[i \
				+ s_fdf->s_map_data.total_column], &(s_fdf->s_isometric));
			ft_draw_line(&(s_fdf->s_mlx_data.s_img), s_line);
			i += s_fdf->s_map_data.total_column;
		}
		i = s_fdf->s_map_data.total_column - column;
		row = s_fdf->s_map_data.total_row;
	}
}
