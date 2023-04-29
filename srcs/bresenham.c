/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:40:37 by shinfray          #+#    #+#             */
/*   Updated: 2023/04/29 17:05:54 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void 	draw_line_sharp(t_img_data *s_img, t_coordinates coordinates);
static void 	draw_line_obtuse(t_img_data *s_img, t_coordinates coordinates);
unsigned int	ft_abs(int number);

void	draw_line(t_img_data *s_img, t_coordinates coordinates)
{
	int	dx = ft_abs(coordinates.x2 - coordinates.x1);
	int	dy = ft_abs(coordinates.y2 - coordinates.y1);
	if (dx > dy)
		draw_line_sharp(s_img, coordinates);
	else
		draw_line_obtuse(s_img, coordinates);
}

unsigned int	ft_abs(int number)
{
	if (number < 0)
		return (-number);
	return (number);
}

static void 	draw_line_sharp(t_img_data *s_img, t_coordinates coordinates)
{
	int			e = ft_abs(coordinates.x2 - coordinates.x1);
	const int	dx = 2 * e;
	const int	dy = 2 * ft_abs(coordinates.y2 - coordinates.y1);
	int			x_increment;
	int			y_increment;

	x_increment = 1;
	if (coordinates.x1 > coordinates.x2)
		x_increment = -1;
	y_increment = 1;
	if (coordinates.y1 > coordinates.y2)
		y_increment = -1;
	while (coordinates.x1 != coordinates.x2)
	{
		ft_pixel_put_image(s_img, coordinates.x1, coordinates.y1, coordinates.color);
		e -= dy;
		if (e < 0)
		{
			coordinates.y1 += y_increment;
			e += dx;
		}
		coordinates.x1 += x_increment;
	}
	ft_pixel_put_image(s_img, coordinates.x1, coordinates.y1, coordinates.color);
}

static void 	draw_line_obtuse(t_img_data *s_img, t_coordinates coordinates)
{
	int			e = ft_abs(coordinates.y2 - coordinates.y1);
	const int	dx = 2 * ft_abs(coordinates.x2 - coordinates.x1);
	const int	dy = 2 * e;
	int			x_increment;
	int			y_increment;

	x_increment = 1;
	if (coordinates.x1 > coordinates.x2)
		x_increment = -1;
	y_increment = 1;
	if (coordinates.y1 > coordinates.y2)
		y_increment = -1;
	while (coordinates.x1 != coordinates.x2)
	{
		ft_pixel_put_image(s_img, coordinates.x1, coordinates.y1, coordinates.color);
		e -= dx;
		if (e < 0)
		{
			coordinates.x1 += x_increment;
			e += dy;
		}
		coordinates.y1 += y_increment;
	}
	ft_pixel_put_image(s_img, coordinates.x1, coordinates.y1, coordinates.color);
}

