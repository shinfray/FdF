/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:39:24 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/20 23:59:55 by shinfray         ###   ########.fr       */
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
	(void)keycode;
	(void)s_fdf;
	// if (keycode == ESCAPE_KEY)
	// 	return (ft_close(param));
	//ft_printf("=====KEY PRESSED=====\nkeycode: %d\n", keycode);
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
	if (keycode == ESCAPE_KEY)
		return (ft_close(s_fdf));
	ft_printf("=====KEY hold=====\nkeycode: %d\n", keycode);
	if (keycode == UP_KEY)
		s_fdf->s_isometric_data.move_y -= 10;
	if (keycode == DOWN_KEY)
		s_fdf->s_isometric_data.move_y += 10;
	if (keycode == LEFT_KEY)
		s_fdf->s_isometric_data.move_x -= 10;
	if (keycode == RIGHT_KEY)
		s_fdf->s_isometric_data.move_x += 10;
	ft_print_map(s_fdf);
	mlx_put_image_to_window(s_fdf->mlx_data.mlx_ptr, s_fdf->mlx_data.win_ptr, s_fdf->mlx_data.s_img.img, 0, 0);

	return (0);
}