/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 03:40:45 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/23 14:20:09 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_reprint_image(t_fdf *s_fdf);
void	ft_reset(t_fdf *s_fdf);
void static	ft_drag_drop(t_fdf *s_fdf, int x, int y);

int	ft_click(int button, int x, int y, t_fdf *s_fdf)
{
	if (button == DOWN_SCROLL || button == UP_SCROLL)
		ft_zoom(s_fdf, button);
	else if (button == LEFT_CLICK && x >= 0 && y >= 0)
		ft_drag_drop(s_fdf, x, y);
	return (0);
}

int	ft_unclick(int button, int x, int y, t_fdf *s_fdf)
{
	if (button == LEFT_CLICK)
		ft_drag_drop(s_fdf, x, y);
	return (0);
}

void static	ft_drag_drop(t_fdf *s_fdf, int x, int y)
{
		s_fdf->s_drag_drop_data.previous_pos_x = s_fdf->s_isometric_data.move_x;
		s_fdf->s_drag_drop_data.previous_pos_y = s_fdf->s_isometric_data.move_y;
		s_fdf->s_drag_drop_data.click_pos_x = x;
		s_fdf->s_drag_drop_data.click_pos_y = y;
		s_fdf->drag_drop_status = s_fdf->drag_drop_status ^ 1;
}

int	ft_move_mouse(int x, int y, t_fdf *s_fdf)
{
	if (s_fdf->drag_drop_status == true)
	{
		s_fdf->s_isometric_data.move_x = x - s_fdf->s_drag_drop_data.click_pos_x + s_fdf->s_drag_drop_data.previous_pos_x;
		s_fdf->s_isometric_data.move_y = y - s_fdf->s_drag_drop_data.click_pos_y + s_fdf->s_drag_drop_data.previous_pos_y;
		ft_reprint_image(s_fdf);
	}
	return (0);
}

int	ft_key_pressed(int keycode, t_fdf *s_fdf)
{
	if (keycode == ESCAPE_KEY)
		return (ft_close(s_fdf));
	else if (keycode == M_KEY)
	{
		s_fdf->toggle_menu = s_fdf->toggle_menu ^ 1;
		mlx_put_image_to_window(s_fdf->s_mlx_data.mlx_ptr, s_fdf->s_mlx_data.win_ptr, s_fdf->s_mlx_data.s_img.img, 0, 0);
		ft_print_help(s_fdf);
	}
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
	s_fdf->s_mlx_data.s_img.addr = mlx_get_data_addr(s_fdf->s_mlx_data.s_img.img, \
			&(s_fdf->s_mlx_data.s_img.bpp), &(s_fdf->s_mlx_data.s_img.line_len), \
			&(s_fdf->s_mlx_data.s_img.endian));
	ft_print_map(s_fdf);
	mlx_put_image_to_window(s_fdf->s_mlx_data.mlx_ptr, s_fdf->s_mlx_data.win_ptr, \
			s_fdf->s_mlx_data.s_img.img, 0, 0);
	ft_print_help(s_fdf);
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


void	ft_move(t_fdf *s_fdf, int keycode)
{
	if (keycode == UP_KEY)
		s_fdf->s_isometric_data.move_y -= 10;
	else if (keycode == DOWN_KEY)
		s_fdf->s_isometric_data.move_y += 10;
	else if (keycode == LEFT_KEY)
		s_fdf->s_isometric_data.move_x -= 10;
	else if (keycode == RIGHT_KEY)
		s_fdf->s_isometric_data.move_x += 10;
	ft_reprint_image(s_fdf);
}

void	ft_height(t_fdf *s_fdf, int keycode)
{
	if (keycode == UP_KEY)
		s_fdf->s_isometric_data.height += 1;
	else if (keycode == DOWN_KEY)
		s_fdf->s_isometric_data.height -= 1;
	ft_reprint_image(s_fdf);
}

void	ft_zoom(t_fdf *s_fdf, int keycode)
{
	if (keycode == UP_KEY || keycode == DOWN_SCROLL)
	{
		s_fdf->s_isometric_data.interspace += s_fdf->s_isometric_data.interspace / 100 * 5;
		s_fdf->s_isometric_data.height += s_fdf->s_isometric_data.height / 100 * 5;
	}
	else if ((keycode == DOWN_KEY || keycode == UP_SCROLL) && s_fdf->s_isometric_data.interspace > 0)
	{
		s_fdf->s_isometric_data.interspace -= s_fdf->s_isometric_data.interspace / 100 * 5;
		s_fdf->s_isometric_data.height -= s_fdf->s_isometric_data.height / 100 * 5;
	}
	ft_reprint_image(s_fdf);
}

void	ft_rotate(t_fdf *s_fdf, int keycode)
{
	if (keycode == UP_KEY)
		s_fdf->s_isometric_data.angle -= ft_rad(1);
	else if (keycode == DOWN_KEY)
		s_fdf->s_isometric_data.angle += ft_rad(1);
	ft_reprint_image(s_fdf);
	// else if (keycode == LEFT_KEY)
	// 	s_fdf->s_isometric_data.move_x -= 10;
	// else if (keycode == RIGHT_KEY)
	// 	s_fdf->s_isometric_data.move_x += 10;
}
