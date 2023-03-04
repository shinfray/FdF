/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:44:59 by shinfray          #+#    #+#             */
/*   Updated: 2023/03/04 18:34:51 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_initialize(t_data *s_window, int width, int height, char *name)
{
	s_window->mlx_ptr = mlx_init();
	if (s_window->mlx_ptr == NULL)
		exit(EXIT_FAILURE);
	s_window->win_ptr = mlx_new_window(s_window->mlx_ptr, width, height, name);
	if (s_window->win_ptr == NULL)
	{
		free(s_window->win_ptr);
		exit(EXIT_FAILURE);
	}
	s_window->s_img.img = mlx_new_image(s_window->mlx_ptr, width, height);
	s_window->s_img.addr = mlx_get_data_addr(s_window->s_img.img, &s_window->s_img.bpp, &s_window->s_img.line_len, &s_window->s_img.endian);
}

void	ft_initialize_hooks(t_data *s_window)
{
	mlx_mouse_hook(s_window->win_ptr, &ft_mouse_click, NULL);
	mlx_key_hook(s_window->win_ptr, &ft_key_pressed, s_window);
	mlx_hook(s_window->win_ptr, ON_DESTROY, 0, &ft_close, s_window);
}

int	main(void)
{
	t_data	s_window;

	ft_initialize(&s_window, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
	ft_draw_rectangle(&s_window.s_img, (t_rect){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0x00FFFFFF});
	draw_line(&s_window.s_img, (t_coordinates){400, 400, 45, 29, 00000000});
	mlx_put_image_to_window(s_window.mlx_ptr, s_window.win_ptr, s_window.s_img.img, 0, 0);
	ft_initialize_hooks(&s_window);
	mlx_loop(s_window.mlx_ptr);
	return (0);
}
