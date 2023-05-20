/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:39:17 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/20 16:41:33 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_pixel_put_image(t_img_data *s_image, int x, int y, int color)
{
	char    *pixel;
	int		i;

	x += 200;
	y += 200;
	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	i = s_image->bpp - 8;
    pixel = s_image->addr + (y * s_image->line_len + x * (s_image->bpp / 8));
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (s_image->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (s_image->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

// int	ft_draw_rectangle(t_img_data *s_img, t_rect s_rect)
// {
// 	int	i;
// 	int	j;

// 	i = s_rect.y;
// 	while (i < s_rect.y + s_rect.height)
// 	{
// 		j = s_rect.x;
// 		while (j < s_rect.x + s_rect.width)
// 			ft_pixel_put_image(s_img, j++, i, s_rect.color);
// 		++i;
// 	}
// 	return (0);
// }

// int	ft_draw_bordure(t_img_data *s_img, t_rect s_rect)
// {
// 	int	i;
// 	int	j;

// 	i = s_rect.y;
// 	j = s_rect.x;
// 	while (j < s_rect.x + s_rect.width)
// 		ft_pixel_put_image(s_img, j++, i, s_rect.color);
// 	++i;
// 	while (i < s_rect.y + s_rect.height - 1)
// 	{
// 		ft_pixel_put_image(s_img, s_rect.x, i, s_rect.color);
// 		ft_pixel_put_image(s_img, s_rect.x + s_rect.width - 1, i, s_rect.color);
// 		++i;
// 	}
// 	j = s_rect.x;
// 	while (j < s_rect.x + s_rect.width)
// 		ft_pixel_put_image(s_img, j++, i, s_rect.color);
// 	return (0);
// }

// #define RED 0x00A576B7

// void ft_draw_circle(t_img_data *s_img, int xc, int yc, int x, int y)
// {
//     ft_pixel_put_image(s_img, xc+x, yc+y, RED);
//     ft_pixel_put_image(s_img, xc-x, yc+y, RED);
//     ft_pixel_put_image(s_img, xc+x, yc-y, RED);
//     ft_pixel_put_image(s_img, xc-x, yc-y, RED);
//     ft_pixel_put_image(s_img, xc+y, yc+x, RED);
//     ft_pixel_put_image(s_img, xc-y, yc+x, RED);
//     ft_pixel_put_image(s_img, xc+y, yc-x, RED);
//     ft_pixel_put_image(s_img, xc-y, yc-x, RED);
// }
 
// // Function for circle-generation
// // using Bresenham's algorithm
// void ft_circle_bres(t_img_data *s_img, int xc, int yc, int r)
// {
//     int x = 0, y = r;
//     int d = 3 - 2 * r;
//     ft_draw_circle(s_img, xc, yc, x, y);
//     while (y >= x)
//     {
//         // for each pixel we will
//         // draw all eight pixels
         
//         x++;
 
//         // check for decision parameter
//         // and correspondingly
//         // update d, x, y
//         if (d > 0)
//         {
//             y--;
//             d = d + 4 * (x - y) + 10;
//         }
//         else
//             d = d + 4 * x + 6;
//         ft_draw_circle(s_img, xc, yc, x, y);
//     }
// }