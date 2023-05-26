/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:25:21 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/23 16:36:221y shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_refresh_interface(t_fdf *s_fdf);
void	ft_print_help_menu(t_fdf *s_fdf);
void	ft_print_actual_mode(t_fdf *s_fdf);

void	ft_refresh_interface(t_fdf *s_fdf)
{
	mlx_put_image_to_window(s_fdf->s_mlx_data.mlx_ptr, \
		s_fdf->s_mlx_data.win_ptr, s_fdf->s_mlx_data.s_img.img, 0, 0);
	ft_print_help_menu(s_fdf);
	ft_print_actual_mode(s_fdf);
}

void	ft_print_help_menu(t_fdf *s_fdf)
{
	if (s_fdf->toggle_menu == false)
		return ;
	mlx_string_put(s_fdf->s_mlx_data.mlx_ptr, s_fdf->s_mlx_data.win_ptr, \
			10, 10, WHITE, "N: NORMAL MODE");
	mlx_string_put(s_fdf->s_mlx_data.mlx_ptr, s_fdf->s_mlx_data.win_ptr, \
			10, 30, WHITE, "H: HEIGHT MODE");
	mlx_string_put(s_fdf->s_mlx_data.mlx_ptr, s_fdf->s_mlx_data.win_ptr, \
			10, 50, WHITE, "Z: ZOOM MODE");
	mlx_string_put(s_fdf->s_mlx_data.mlx_ptr, s_fdf->s_mlx_data.win_ptr, \
			10, 70, WHITE, "R: ROTATE MODE");
	mlx_string_put(s_fdf->s_mlx_data.mlx_ptr, s_fdf->s_mlx_data.win_ptr, \
			10, 90, WHITE, "X: RESET");
	mlx_string_put(s_fdf->s_mlx_data.mlx_ptr, s_fdf->s_mlx_data.win_ptr, \
			10, 110, WHITE, "M: TOGGLE HELP MENU");
	mlx_string_put(s_fdf->s_mlx_data.mlx_ptr, s_fdf->s_mlx_data.win_ptr, \
			10, 130, WHITE, "USE ARROW KEYS");
	mlx_string_put(s_fdf->s_mlx_data.mlx_ptr, s_fdf->s_mlx_data.win_ptr, \
			10, 150, WHITE, "USE , AND . FOR THE THIRD ROTATION");
}

void	ft_print_actual_mode(t_fdf *s_fdf)
{
	const char	*mode[4] = {"NORMAL MODE", \
							"HEIGHT MODE", \
							"ZOOM MODE", \
							"ROTATE MODE"};

	mlx_string_put(s_fdf->s_mlx_data.mlx_ptr, s_fdf->s_mlx_data.win_ptr, \
		10, WINDOW_HEIGHT - 30, WHITE, (char *)mode[s_fdf->mode]);
}
