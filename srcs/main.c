/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:44:59 by shinfray          #+#    #+#             */
/*   Updated: 2023/01/31 19:56:10 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720

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
	while (i < s_rect.y + s_rect.height)
	{
		j = s_rect.x;
		while (j < s_rect.x + s_rect.width)
			ft_pixel_put_image(img, j++, i, s_rect.color);
		++i;
	}
	return (0);
}

int	ft_draw_bordure(t_image_data *img, t_rect s_rect)
{
	int	i;
	int	j;


	i = s_rect.y;
	j = s_rect.x;
	while (j < s_rect.x + s_rect.width)
		ft_pixel_put_image(img, j++, i, s_rect.color);
	++i;
	while (i < s_rect.y + s_rect.height - 1)
	{
		ft_pixel_put_image(img, s_rect.x, i, s_rect.color);
		ft_pixel_put_image(img, s_rect.x + s_rext.width - 1, i, s_rect.color);
		++i;
	}
	j = s_rect.x;
	while (j < s_rect.x + s_rect.width)
		ft_pixel_put_image(img, j++, i, s_rect.color);
	return (0);
}

int	main(void)
{
	t_data	window;

	window.mlx_ptr = mlx_init();
	if (window.mlx_ptr == NULL)
		exit(EXIT_FAILURE);
	window.win_ptr = mlx_new_window(window.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
	if (window.win_ptr == NULL)
	{
		free(window.win_ptr);
		exit(EXIT_FAILURE);
	}
	window.s_image.image = mlx_new_image(window.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	window.s_image.address = mlx_get_data_addr(window.s_image.image, &window.s_image.bpp, &window.s_image.line_length, &window.s_image.endian);
	ft_draw_rectangle(&window.s_image, (t_rect){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0x00FFFFFF});
	ft_draw_rectangle(&window.s_image, (t_rect){0, 0, 50, 50, 0x004a78b6});
	ft_draw_rectangle(&window.s_image, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 100, 100, 0x00E398AB});
	mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, window.s_image.image, 0, 0);
	mlx_mouse_hook(window.win_ptr, &ft_check_mouse_click, NULL);
	mlx_key_hook(window.win_ptr, &ft_check_key_pressed, &window);
	mlx_hook(window.win_ptr, ON_DESTROY, 0, &ft_close, &window);
	mlx_loop(window.mlx_ptr);

	return (0);
}
