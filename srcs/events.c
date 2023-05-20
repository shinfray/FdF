/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:39:24 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/21 01:23:37by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_mouse_click(int button, int x, int y, t_fdf *s_fdf)
{
	(void)s_fdf;
	ft_printf("=====MOUSE=====\nbutton number: %d\nx: %d\ny: %d\n", button, x, y);
	return (0);
}

int	ft_key_pressed(int keycode, t_fdf *s_fdf)
{
	if (keycode == ESCAPE_KEY)
		return (ft_close(s_fdf));
	if (keycode == N_KEY)
		s_fdf->mode = NORMAL_MODE;
	if (keycode == R_KEY)
		s_fdf->mode = ROTATE_MODE;
	else if (keycode == Z_KEY)
		s_fdf->mode = ZOOM_MODE;
	else if (keycode == H_KEY)
		s_fdf->mode = HEIGHT_MODE;
	return (0);
}

int	ft_close(t_fdf *s_fdf)
{
	mlx_destroy_window(s_fdf->mlx_data.mlx_ptr, s_fdf->mlx_data.win_ptr);
	free(s_fdf->mlx_data.mlx_ptr);
	if (s_fdf->map_data.map != NULL)
		free(s_fdf->map_data.map);
	exit(EXIT_SUCCESS);
}

int	ft_hold_key(int keycode, t_fdf *s_fdf)
{
	void	(*ft_mode[3])(t_fdf *, int);

	(ft_mode[0]) = &ft_move;
	(ft_mode[0]) = &ft_height;
	(ft_mode[0]) = &ft_zoom;

	if (keycode != UP_KEY || keycode != DOWN_KEY || keycode != LEFT_KEY || keycode != RIGHT_KEY)
		return (0);

	printf("holdkey;%d\n", keycode);
	(*ft_mode[s_fdf->mode])(s_fdf, keycode);
	ft_print_map(s_fdf);
	mlx_put_image_to_window(s_fdf->mlx_data.mlx_ptr, s_fdf->mlx_data.win_ptr, s_fdf->mlx_data.s_img.img, 0, 0);
	return (0);
}

void	ft_move(t_fdf *s_fdf, int keycode)
{
	if (keycode == UP_KEY)
		s_fdf->s_isometric_data.move_y -= 10;
	if (keycode == DOWN_KEY)
		s_fdf->s_isometric_data.move_y += 10;
	if (keycode == LEFT_KEY)
		s_fdf->s_isometric_data.move_x -= 10;
	if (keycode == RIGHT_KEY)
		s_fdf->s_isometric_data.move_x += 10;
}

void	ft_height(t_fdf *s_fdf, int keycode)
{
	if (keycode == UP_KEY)
		s_fdf->s_isometric_data.height += 1;
	else if (keycode == DOWN_KEY)
		s_fdf->s_isometric_data.height -= 1;
}

void	ft_zoom(t_fdf *s_fdf, int keycode)
{
	if (keycode == UP_KEY)
		s_fdf->s_isometric_data.interspace += 2;
	else if (keycode == DOWN_KEY)
		s_fdf->s_isometric_data.interspace -= 2;
}