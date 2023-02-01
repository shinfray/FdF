/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:44:59 by shinfray          #+#    #+#             */
/*   Updated: 2023/02/01 14:41:48 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720

void	ft_pixel_put_image(t_img_data *s_image, int x, int y, int color)
{
	char    *pixel;
	int		i;

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

int	ft_mouse_click(int button, int x, int y, void *param)
{
	(void)param;
	ft_printf("=====MOUSE=====\nbutton number: %d\nx: %d\ny: %d\n", button, x, y);
	return (0);
}

int	ft_key_pressed(int keycode, t_data *param)
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

int	ft_draw_rectangle(t_img_data *s_img, t_rect s_rect)
{
	int	i;
	int	j;

	i = s_rect.y;
	while (i < s_rect.y + s_rect.height)
	{
		j = s_rect.x;
		while (j < s_rect.x + s_rect.width)
			ft_pixel_put_image(s_img, j++, i, s_rect.color);
		++i;
	}
	return (0);
}

int	ft_draw_bordure(t_img_data *s_img, t_rect s_rect)
{
	int	i;
	int	j;


	i = s_rect.y;
	j = s_rect.x;
	while (j < s_rect.x + s_rect.width)
		ft_pixel_put_image(s_img, j++, i, s_rect.color);
	++i;
	while (i < s_rect.y + s_rect.height - 1)
	{
		ft_pixel_put_image(s_img, s_rect.x, i, s_rect.color);
		ft_pixel_put_image(s_img, s_rect.x + s_rect.width - 1, i, s_rect.color);
		++i;
	}
	j = s_rect.x;
	while (j < s_rect.x + s_rect.width)
		ft_pixel_put_image(s_img, j++, i, s_rect.color);
	return (0);
}

#define RED 0x00A576B7

void drawCircle(t_img_data *s_img, int xc, int yc, int x, int y)
{
    ft_pixel_put_image(s_img, xc+x, yc+y, RED);
    ft_pixel_put_image(s_img, xc-x, yc+y, RED);
    ft_pixel_put_image(s_img, xc+x, yc-y, RED);
    ft_pixel_put_image(s_img, xc-x, yc-y, RED);
    ft_pixel_put_image(s_img, xc+y, yc+x, RED);
    ft_pixel_put_image(s_img, xc-y, yc+x, RED);
    ft_pixel_put_image(s_img, xc+y, yc-x, RED);
    ft_pixel_put_image(s_img, xc-y, yc-x, RED);
}
 
// Function for circle-generation
// using Bresenham's algorithm
void circleBres(t_img_data *s_img, int xc, int yc, int r)
{
    int x = 0, y = r;
    int d = 3 - 2 * r;
    drawCircle(s_img, xc, yc, x, y);
    while (y >= x)
    {
        // for each pixel we will
        // draw all eight pixels
         
        x++;
 
        // check for decision parameter
        // and correspondingly
        // update d, x, y
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;
        drawCircle(s_img, xc, yc, x, y);
    }
}

int	main(void)
{
	t_data	s_window;

	s_window.mlx_ptr = mlx_init();
	if (s_window.mlx_ptr == NULL)
		exit(EXIT_FAILURE);
	s_window.win_ptr = mlx_new_window(s_window.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
	if (s_window.win_ptr == NULL)
	{
		free(s_window.win_ptr);
		exit(EXIT_FAILURE);
	}
	s_window.s_img.img = mlx_new_image(s_window.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	s_window.s_img.addr = mlx_get_data_addr(s_window.s_img.img, &s_window.s_img.bpp, &s_window.s_img.line_len, &s_window.s_img.endian);
	ft_draw_rectangle(&s_window.s_img, (t_rect){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0x00FFFFFF});
	ft_draw_rectangle(&s_window.s_img, (t_rect){0, 0, 50, 50, 0x004a78b6});
	ft_draw_rectangle(&s_window.s_img, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 100, 100, 0x00E398AB});
	ft_draw_bordure(&s_window.s_img, (t_rect){200, 200, 200, 200, 0x004a78b6});
	circleBres(&s_window.s_img, 150, 150, 100); 
	mlx_put_image_to_window(s_window.mlx_ptr, s_window.win_ptr, s_window.s_img.img, 0, 0);
	mlx_mouse_hook(s_window.win_ptr, &ft_mouse_click, NULL);
	mlx_key_hook(s_window.win_ptr, &ft_key_pressed, &s_window);
	mlx_hook(s_window.win_ptr, ON_DESTROY, 0, &ft_close, &s_window);
	mlx_loop(s_window.mlx_ptr);

	return (0);
}
