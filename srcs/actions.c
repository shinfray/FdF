/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:39:08 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/23 16:45:06 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_move(t_fdf *s_fdf, int keycode);
void	ft_height(t_fdf *s_fdf, int keycode);
void	ft_zoom(t_fdf *s_fdf, int keycode);
void	ft_rotate(t_fdf *s_fdf, int keycode);

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
		s_fdf->s_isometric_data.interspace += \
			(s_fdf->s_isometric_data.interspace / 100 * 5);
		s_fdf->s_isometric_data.height += \
			(s_fdf->s_isometric_data.height / 100 * 5);
	}
	else if ((keycode == DOWN_KEY || keycode == UP_SCROLL) \
		&& s_fdf->s_isometric_data.interspace > 0)
	{
		s_fdf->s_isometric_data.interspace -= \
			(s_fdf->s_isometric_data.interspace / 100 * 5);
		s_fdf->s_isometric_data.height -= \
			(s_fdf->s_isometric_data.height / 100 * 5);
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
}
