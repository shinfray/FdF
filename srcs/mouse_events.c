/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:47:34 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/27 01:32:02 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			ft_click(int button, int x, int y, t_fdf *s_fdf);
int			ft_unclick(int button, int x, int y, t_fdf *s_fdf);
int			ft_move_mouse(int x, int y, t_fdf *s_fdf);
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
	if (button == LEFT_CLICK && s_fdf->drag_drop_status == true)
		ft_drag_drop(s_fdf, x, y);
	return (0);
}

int	ft_move_mouse(int x, int y, t_fdf *s_fdf)
{
	if (s_fdf->drag_drop_status == true)
	{
		s_fdf->s_isometric.move_x = x \
			- s_fdf->s_drag_drop_data.click_pos_x \
			+ s_fdf->s_drag_drop_data.previous_pos_x;
		s_fdf->s_isometric.move_y = y \
			- s_fdf->s_drag_drop_data.click_pos_y \
			+ s_fdf->s_drag_drop_data.previous_pos_y;
		ft_reprint_image(s_fdf);
	}
	return (0);
}

void static	ft_drag_drop(t_fdf *s_fdf, int x, int y)
{
		s_fdf->s_drag_drop_data.previous_pos_x = s_fdf->s_isometric.move_x;
		s_fdf->s_drag_drop_data.previous_pos_y = s_fdf->s_isometric.move_y;
		s_fdf->s_drag_drop_data.click_pos_x = x;
		s_fdf->s_drag_drop_data.click_pos_y = y;
		s_fdf->drag_drop_status = s_fdf->drag_drop_status ^ 1;
}
