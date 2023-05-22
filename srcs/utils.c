/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:59:05 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/22 17:59:44 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_print_help(t_fdf *s_fdf)
{
	if (s_fdf->toggle_menu == false)
		return ;
	mlx_string_put(s_fdf->s_mlx_data.mlx_ptr, s_fdf->s_mlx_data.win_ptr, \
			10, 10, 0xFFFFFF, "N: NORMAL MODE");
	mlx_string_put(s_fdf->s_mlx_data.mlx_ptr, s_fdf->s_mlx_data.win_ptr, \
			10, 30, 0xFFFFFF, "Z: ZOOM MODE");
	mlx_string_put(s_fdf->s_mlx_data.mlx_ptr, s_fdf->s_mlx_data.win_ptr, \
			10, 50, 0xFFFFFF, "R: ROTATE MODE");
	mlx_string_put(s_fdf->s_mlx_data.mlx_ptr, s_fdf->s_mlx_data.win_ptr, \
			10, 70, 0xFFFFFF, "H: HEIGHT MODE");
	mlx_string_put(s_fdf->s_mlx_data.mlx_ptr, s_fdf->s_mlx_data.win_ptr, \
			10, 90, 0xFFFFFF, "USE ARROW KEYS");
	mlx_string_put(s_fdf->s_mlx_data.mlx_ptr, s_fdf->s_mlx_data.win_ptr, \
			10, 110, 0xFFFFFF, "M: TOGGLE HELP MENU");
}