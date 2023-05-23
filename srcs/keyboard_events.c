/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:12:39 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/23 19:24:43 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_key_pressed(int keycode, t_fdf *s_fdf);
int	ft_hold_key(int keycode, t_fdf *s_fdf);

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
