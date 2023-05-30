/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:40:37 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/30 16:21:04 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				ft_draw_line(t_img *s_img, t_line *s_line);
void				ft_pixel_put(t_img *s_image, t_point *s_point);
static unsigned int	ft_abs(int number);

/*
 *	In the "else" case, in the loop inside this function,
 *	we fall into the case where : (s_bresenham.error * 2) <= dx
 */
void	ft_draw_line(t_img *s_img, t_line *s_line)
{
	const int	dx = ft_abs(s_line->end.x - s_line->start.x);
	const int	dy = -ft_abs(s_line->end.y - s_line->start.y);
	t_bresenham	s_bresenham;

	s_bresenham.sign_x = 1;
	s_bresenham.sign_y = 1;
	if (s_line->start.x >= s_line->end.x)
		s_bresenham.sign_x = -1;
	if (s_line->start.y >= s_line->end.y)
		s_bresenham.sign_y = -1;
	s_bresenham.error = dx + dy;
	while (s_line->start.x != s_line->end.x || s_line->start.y != s_line->end.y)
	{
		ft_pixel_put(s_img, &(s_line->start));
		if (s_bresenham.error * 2 >= dy)
		{
			s_bresenham.error += dy;
			s_line->start.x += s_bresenham.sign_x;
		}
		else
		{
			s_bresenham.error += dx;
			s_line->start.y += s_bresenham.sign_y;
		}
	}
}

/*
 *	In the loop inside this function:
 *	- the "if" case concern the big endian (MSB is the leftmost bit).
 *	- the "else" case concern tle little endian (LSB is the leftmost bit).
 */
void	ft_pixel_put(t_img *s_image, t_point *s_point)
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

static unsigned int	ft_abs(int number)
{
	if (number < 0)
		return (-number);
	return (number);
}
