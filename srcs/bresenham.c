/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:40:37 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/18 18:11:49 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void 	draw_line_sharp(t_img_data *s_img, t_point start, t_point end);
static void 	draw_line_obtuse(t_img_data *s_img, t_point start, t_point end);
unsigned int	ft_abs(int number);

void	ft_draw_line(t_img_data *s_img, t_point start, t_point end)
{
	int	dx = ft_abs(end.x - start.x);
	int	dy = ft_abs(end.y - start.y);
	if (dx > dy)
		draw_line_sharp(s_img, start, end);
	else
		draw_line_obtuse(s_img, start, end);
}

unsigned int	ft_abs(int number)
{
	if (number < 0)
		return (-number);
	return (number);
}

static void 	draw_line_sharp(t_img_data *s_img, t_point start, t_point end)
{
	int			e = ft_abs(end.x - start.x);
	const int	dx = 2 * e;
	const int	dy = 2 * ft_abs(end.y - start.y);
	int			x_increment;
	int			y_increment;

	x_increment = 1;
	if (start.x > end.x)
		x_increment = -1;
	y_increment = 1;
	if (start.y > end.y)
		y_increment = -1;
	while (start.x != end.x)
	{
		ft_pixel_put_image(s_img, start.x, start.y, start.color);
		e -= dy;
		if (e < 0)
		{
			start.y += y_increment;
			e += dx;
		}
		start.x += x_increment;
	}
	ft_pixel_put_image(s_img, start.x, start.y, start.color);
}

static void 	draw_line_obtuse(t_img_data *s_img, t_point start, t_point end)
{
	int			e = ft_abs(end.y - start.y);
	const int	dx = 2 * ft_abs(end.x - start.x);
	const int	dy = 2 * e;
	int			x_increment;
	int			y_increment;

	x_increment = 1;
	if (start.x > end.x)
		x_increment = -1;
	y_increment = 1;
	if (start.y > end.y)
		y_increment = -1;
	while (start.x != end.x)
	{
		ft_pixel_put_image(s_img, start.x, start.y, start.color);
		e -= dx;
		if (e < 0)
		{
			start.x += x_increment;
			e += dy;
		}
		start.y += y_increment;
	}
	ft_pixel_put_image(s_img, start.x, start.y, start.color);
}

