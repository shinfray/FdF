/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:39:17 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/22 17:37:53 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_pixel_put_image(t_img_data *s_image, int x, int y, int colour)
{
	char	*pixel;
	int		i;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	i = s_image->bpp - 8;
	pixel = s_image->addr + (y * s_image->line_len + x * (s_image->bpp / 8));
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (s_image->endian != 0)
			*pixel++ = (colour >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (colour >> (s_image->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}