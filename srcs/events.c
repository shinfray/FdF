/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:39:24 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/20 18:36:15 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_mouse_click(int button, int x, int y, t_mlx_data *param)
{
	(void)param;
	ft_printf("=====MOUSE=====\nbutton number: %d\nx: %d\ny: %d\n", button, x, y);
	return (0);
}

int	ft_key_pressed(int keycode, t_mlx_data *param)
{
	(void)keycode;
	(void)param;
	// if (keycode == ESCAPE_KEY)
	// 	return (ft_close(param));
	//ft_printf("=====KEY PRESSED=====\nkeycode: %d\n", keycode);
	return (0);
}

int	ft_close(t_mlx_data *param)
{
	mlx_destroy_window(param->mlx_ptr, param->win_ptr);
	free(param->mlx_ptr);
	exit(EXIT_SUCCESS);
}

int	ft_hold_key(int keycode, t_fdf *s_fdf)
{
	if (keycode == ESCAPE_KEY)
		return (ft_close(&(s_fdf->mlx_data)));
	ft_printf("=====KEY hold=====\nkeycode: %d\n", keycode);
	if (keycode == UP_KEY)
		s_fdf->s_isometric_data.move_y -= 1;
	if (keycode == DOWN_KEY)
		s_fdf->s_isometric_data.move_y += 1;
	if (keycode == LEFT_KEY)
		s_fdf->s_isometric_data.move_x -= 1;
	if (keycode == RIGHT_KEY)
		s_fdf->s_isometric_data.move_y += 1;
	ft_print_map(s_fdf);

	return (0);
}