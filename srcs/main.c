/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:44:59 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/20 17:44:45 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_initialize_fdf_data(t_fdf *s_fdf, char *path);
static void	ft_initialize_window(t_mlx_data *s_window);
static void	ft_set_hooks(t_mlx_data *s_window);

int	main(int argc, char **argv)
{
	t_fdf	s_fdf;

	if (argc != 2)
	{
		errno = 22;
		perror("ERROR");
		exit(EXIT_FAILURE);
	}
	ft_initialize_fdf_data(&s_fdf, argv[1]);
	
	ft_parse_map(&s_fdf);

	ft_initialize_window(&(s_fdf.mlx_data));
	ft_print_map(&s_fdf);
	//ft_draw_rectangle(&s_window.s_img, (t_rect){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFFFFFF});
	//ft_draw_line(&s_window.s_img, (t_point){483, 46, 0, 0x00FF0000, 0}, (t_point){12, 72, 0, 0x00FF0000, 0});
	mlx_put_image_to_window(s_fdf.mlx_data.mlx_ptr, s_fdf.mlx_data.win_ptr, s_fdf.mlx_data.s_img.img, 0, 0);
	ft_set_hooks(&(s_fdf.mlx_data));
	mlx_loop(s_fdf.mlx_data.mlx_ptr);
	return (0);
}

static void	ft_initialize_fdf_data(t_fdf *s_fdf, char *path)
{
	s_fdf->s_file_data.fd = -1;
	s_fdf->s_file_data.path = path;
	s_fdf->s_isometric_data.interspace = 10;
	s_fdf->s_isometric_data.height = 3;
	s_fdf->s_isometric_data.angle = 30;
	s_fdf->s_isometric_data.origin_x = 200;
	s_fdf->s_isometric_data.origin_y = 200;
}

static void	ft_initialize_window(t_mlx_data *s_window)
{
	s_window->mlx_ptr = mlx_init();
	if (s_window->mlx_ptr == NULL)
		exit(EXIT_FAILURE);
	s_window->win_ptr = mlx_new_window(s_window->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
	if (s_window->win_ptr == NULL)
	{
		free(s_window->win_ptr);
		exit(EXIT_FAILURE);
	}
	s_window->s_img.img = mlx_new_image(s_window->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	s_window->s_img.addr = mlx_get_data_addr(s_window->s_img.img, &s_window->s_img.bpp, &s_window->s_img.line_len, &s_window->s_img.endian);
}

static void	ft_set_hooks(t_mlx_data *s_window)
{
	mlx_mouse_hook(s_window->win_ptr, &ft_mouse_click, s_window);
	mlx_key_hook(s_window->win_ptr, &ft_key_pressed, s_window);
	mlx_hook(s_window->win_ptr, ON_DESTROY, 0, &ft_close, s_window);
}