/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:39:08 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/28 10:14:36 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_move(t_fdf *s_fdf, int keycode);
void	ft_height(t_fdf *s_fdf, int keycode);
void	ft_zoom(t_fdf *s_fdf, int keycode);
void	ft_rotate(t_fdf *s_fdf, int keycode);
void	ft_reset(t_fdf *s_fdf);

void	ft_move(t_fdf *s_fdf, int keycode)
{
	if (keycode == UP_KEY)
		s_fdf->s_isometric.move_y -= 5;
	else if (keycode == DOWN_KEY)
		s_fdf->s_isometric.move_y += 5;
	else if (keycode == LEFT_KEY)
		s_fdf->s_isometric.move_x -= 5;
	else if (keycode == RIGHT_KEY)
		s_fdf->s_isometric.move_x += 5;
	ft_reprint_image(s_fdf);
}

void	ft_height(t_fdf *s_fdf, int keycode)
{
	if (keycode == UP_KEY)
		s_fdf->s_isometric.height += 1;
	else if (keycode == DOWN_KEY)
		s_fdf->s_isometric.height -= 1;
	ft_reprint_image(s_fdf);
}

void	ft_zoom(t_fdf *s_fdf, int keycode)
{
	if (keycode == UP_KEY || keycode == DOWN_SCROLL)
	{
		s_fdf->s_isometric.interspace += \
			(s_fdf->s_isometric.interspace / 100 * 3);
		s_fdf->s_isometric.height += \
			(s_fdf->s_isometric.height / 100 * 3);
	}
	else if ((keycode == DOWN_KEY || keycode == UP_SCROLL) \
		&& s_fdf->s_isometric.interspace > 0)
	{
		s_fdf->s_isometric.interspace -= \
			(s_fdf->s_isometric.interspace / 100 * 3);
		s_fdf->s_isometric.height -= \
			(s_fdf->s_isometric.height / 100 * 3);
	}
	ft_reprint_image(s_fdf);
}

void	ft_rotate(t_fdf *s_fdf, int keycode)
{
	if (keycode == UP_KEY)
		s_fdf->s_isometric.angle_x += ft_rad(1);
	else if (keycode == DOWN_KEY)
		s_fdf->s_isometric.angle_x -= ft_rad(1);
	else if (keycode == LEFT_KEY)
		s_fdf->s_isometric.angle_y -= ft_rad(1);
	else if (keycode == RIGHT_KEY)
		s_fdf->s_isometric.angle_y += ft_rad(1);
	else if (keycode == COMMA_KEY)
		s_fdf->s_isometric.angle_z -= ft_rad(1);
	else if (keycode == POINT_KEY)
		s_fdf->s_isometric.angle_z += ft_rad(1);
	ft_reprint_image(s_fdf);
}

void	ft_reset(t_fdf *s_fdf)
{
	ft_set_fdf_data(s_fdf, s_fdf->s_file.path);
	ft_reprint_image(s_fdf);
}
