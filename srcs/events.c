/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 03:40:45 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/23 16:58:45 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_reset(t_fdf *s_fdf);

int	ft_key_pressed(int keycode, t_fdf *s_fdf)
{
	if (keycode == ESCAPE_KEY)
		return (ft_close(s_fdf));
	else if (keycode == M_KEY)
		ft_refresh_interface(s_fdf);
	else if (keycode == N_KEY)
		s_fdf->mode = NORMAL_MODE;
	else if (keycode == R_KEY)
		s_fdf->mode = ROTATE_MODE;
	else if (keycode == Z_KEY)
		s_fdf->mode = ZOOM_MODE;
	else if (keycode == H_KEY)
		s_fdf->mode = HEIGHT_MODE;
	else if (keycode == X_KEY)
		ft_reset(s_fdf);
	if (keycode == N_KEY || keycode == R_KEY \
		|| keycode == Z_KEY || keycode == H_KEY)
		ft_refresh_interface(s_fdf);
	return (0);
}

void	ft_reset(t_fdf *s_fdf)
{
	ft_set_fdf_data(s_fdf, s_fdf->s_file_data.path);
	ft_reprint_image(s_fdf);
}

int	ft_close(t_fdf *s_fdf)
{
	mlx_destroy_image(s_fdf->s_mlx_data.mlx_ptr, s_fdf->s_mlx_data.s_img.img);
	mlx_destroy_window(s_fdf->s_mlx_data.mlx_ptr, s_fdf->s_mlx_data.win_ptr);
	free(s_fdf->s_mlx_data.mlx_ptr);
	if (s_fdf->s_map_data.s_map != NULL)
		free(s_fdf->s_map_data.s_map);
	exit(s_fdf->exit_status);
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
		ft_close(s_fdf);
	}
	s_fdf->s_mlx_data.s_img.addr = \
			mlx_get_data_addr(s_fdf->s_mlx_data.s_img.img, \
			&(s_fdf->s_mlx_data.s_img.bpp), \
			&(s_fdf->s_mlx_data.s_img.line_len), \
			&(s_fdf->s_mlx_data.s_img.endian));
	ft_print_map(s_fdf);
	ft_refresh_interface(s_fdf);
	mlx_destroy_image(s_fdf->s_mlx_data.mlx_ptr, backup);
}

int	ft_hold_key(int keycode, t_fdf *s_fdf)
{
	void		(*ft_mode[4])(t_fdf *, int);

	if (keycode != UP_KEY && keycode != DOWN_KEY \
			&& keycode != LEFT_KEY && keycode != RIGHT_KEY)
		return (0);
	(ft_mode[0]) = &ft_move;
	(ft_mode[1]) = &ft_height;
	(ft_mode[2]) = &ft_zoom;
	(ft_mode[3]) = &ft_rotate;
	(*ft_mode[s_fdf->mode])(s_fdf, keycode);
	return (0);
}
