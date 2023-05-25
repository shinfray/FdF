/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:40:37 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/25 21:44:13 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				ft_draw_line(t_img_data *s_img, t_line *s_line);
void				ft_pixel_put(t_img_data *s_image, t_point *s_point);
static void			ft_draw_sharp_line(t_img_data *s_img, t_line *s_line);
static void			ft_draw_obtuse_line(t_img_data *s_img, t_line *s_line);
static unsigned int	ft_abs(int number);

void	ft_draw_line(t_img_data *s_img, t_line *s_line)
{
	int	dx;
	int	dy;

	dx = ft_abs(s_line->end.x - s_line->start.x);
	dy = ft_abs(s_line->end.y - s_line->start.y);
	if (dx > dy)
		ft_draw_sharp_line(s_img, s_line);
	else
		ft_draw_obtuse_line(s_img, s_line);
}

/*
 *	In the loop inside this function:
 *	- the "if" case concern the big endian (MSB is the leftmost bit).
 *	- the "else" case concern tle little endian (LSB is the leftmost bit).
 *
 */
void	ft_pixel_put(t_img_data *s_image, t_point *s_point)
{
	char	*pixel;
	int		i;

	if (s_point->x < 0 || s_point->x >= WINDOW_WIDTH \
		|| s_point->y < 0 || s_point->y >= WINDOW_HEIGHT)
		return ;
	i = s_image->bpp - 8;
	pixel = s_image->addr \
		+ (s_point->y * s_image->line_len + s_point->x * (s_image->bpp / 8));
	while (i >= 0)
	{
		if (s_image->endian != 0)
			*pixel++ = (s_point->colour >> i) & 0xFF;
		else
			*pixel++ = (s_point->colour >> (s_image->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

static void	ft_draw_sharp_line(t_img_data *s_img, t_line *s_line)
{
	const int	dx = 2 * ft_abs(s_line->end.x - s_line->start.x);
	const int	dy = 2 * ft_abs(s_line->end.y - s_line->start.y);
	int			e;
	int			x_increment;
	int			y_increment;

	e = ft_abs(s_line->end.x - s_line->start.x);
	x_increment = 1;
	if (s_line->start.x > s_line->end.x)
		x_increment = -1;
	y_increment = 1;
	if (s_line->start.y > s_line->end.y)
		y_increment = -1;
	while (s_line->start.x != s_line->end.x)
	{
		ft_pixel_put(s_img, &(s_line->start));
		e -= dy;
		if (e < 0)
		{
			s_line->start.y += y_increment;
			e += dx;
		}
		s_line->start.x += x_increment;
	}
	ft_pixel_put(s_img, &(s_line->start));
}

static void	ft_draw_obtuse_line(t_img_data *s_img, t_line *s_line)
{
	const int	dx = 2 * ft_abs(s_line->end.x - s_line->start.x);
	const int	dy = 2 * ft_abs(s_line->end.y - s_line->start.y);
	int			e;
	int			x_increment;
	int			y_increment;

	e = ft_abs(s_line->end.y - s_line->start.y);
	x_increment = 1;
	if (s_line->start.x > s_line->end.x)
		x_increment = -1;
	y_increment = 1;
	if (s_line->start.y > s_line->end.y)
		y_increment = -1;
	while (s_line->start.x != s_line->end.x)
	{
		ft_pixel_put(s_img, &(s_line->start));
		e -= dx;
		if (e < 0)
		{
			s_line->start.x += x_increment;
			e += dy;
		}
		s_line->start.y += y_increment;
	}
	ft_pixel_put(s_img, &(s_line->start));
}

static unsigned int	ft_abs(int number)
{
	if (number < 0)
		return (-number);
	return (number);
}
