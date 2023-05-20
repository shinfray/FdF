/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:44:59 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/20 11:14:30 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_initialize(t_data *s_window, int width, int height, char *name);
static void	ft_set_hooks(t_data *s_window);

int	main(int argc, char **argv)
{
	t_data		s_window;
	t_map_data	s_map_data;

	if (argc != 2)
	{
		errno = 22;
		perror("ERROR");
		exit(EXIT_FAILURE);
	}
	
	ft_parse_map(argv[1], &s_map_data);

	ft_initialize(&s_window, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
	ft_print_map(&s_map_data, &s_window.s_img, 20, 3);
	//ft_draw_rectangle(&s_window.s_img, (t_rect){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFFFFFF});
	//ft_draw_line(&s_window.s_img, (t_point){483, 46, 0, 0x00FF0000, 0}, (t_point){12, 72, 0, 0x00FF0000, 0});
	mlx_put_image_to_window(s_window.mlx_ptr, s_window.win_ptr, s_window.s_img.img, 0, 0);
	ft_set_hooks(&s_window);
	mlx_loop(s_window.mlx_ptr);
	return (0);
}

static void	ft_initialize(t_data *s_window, int width, int height, char *name)
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

static void	ft_set_hooks(t_data *s_window)
{
	mlx_mouse_hook(s_window->win_ptr, &ft_mouse_click, s_window);
	mlx_key_hook(s_window->win_ptr, &ft_key_pressed, s_window);
	mlx_hook(s_window->win_ptr, ON_DESTROY, 0, &ft_close, s_window);
}