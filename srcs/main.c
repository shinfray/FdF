/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:44:59 by shinfray          #+#    #+#             */
/*   Updated: 2023/01/31 18:47:22 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

void	ft_pixel_put_image(t_image_data *image, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = image->bpp - 8;
    pixel = image->address + (y * image->line_length + x * (image->bpp / 8));
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (image->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (image->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

int	ft_check_mouse_click(int button, int x, int y, void *param)
{
	(void)param;
	ft_printf("=====MOUSE=====\nbutton number: %d\nx: %d\ny: %d\n", button, x, y);
	return (0);
}

int	ft_check_key_pressed(int keycode, t_data *param)
{
	(void)param;
	ft_printf("=====KEY PRESSED=====\nkeycode: %d\n", keycode);
	return (0);
}

int	ft_close(t_data *param)
{
	mlx_destroy_window(param->mlx_ptr, param->win_ptr);
	free(param->mlx_ptr);
	exit(EXIT_SUCCESS);
	return (0);
}

int	ft_draw_rectangle(t_image_data *img, t_rect s_rect)
{
	int	i;
	int	j;

	i = s_rect.y;
	j = s_rect.x;
	while (i < s_rect.y + s_rect.height)
	{
		while (j < s_rect.x + s_rect.width)
			ft_pixel_put_image(img, j++, i, s_rect.color);
		++i;
	}
	return (0);
}

int	main(void)
{
	t_data	window;
	t_rect	s_rect;
	//unsigned int	color;

	s_rect.x = 0;
	s_rect.y = 0;
	s_rect.width = 100;
	s_rect.height = 50;
	s_rect.color = 0xFFFFFF;
	window.mlx_ptr = mlx_init();
	if (window.mlx_ptr == NULL)
		exit(EXIT_FAILURE);
	window.win_ptr = mlx_new_window(window.mlx_ptr, 1920, 1080, "FdF");
	if (window.win_ptr == NULL)
	{
		free(window.win_ptr);
		exit(EXIT_FAILURE);
	}
	window.s_image.image = mlx_new_image(window.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	window.s_image.address = mlx_get_data_addr(window.s_image.image, &window.s_image.bpp, &window.s_image.line_length, &window.s_image.endian);
	ft_draw_rectangle(&window.s_image, s_rect);
	mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, window.s_image.image, 0, 0);
	mlx_mouse_hook(window.win_ptr, &ft_check_mouse_click, NULL);
	mlx_key_hook(window.win_ptr, &ft_check_key_pressed, &window);
	mlx_hook(window.win_ptr, ON_DESTROY, 0, &ft_close, &window);
	mlx_loop(window.mlx_ptr);

	return (0);
}
