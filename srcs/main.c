/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:44:59 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/22 18:01:54 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_initialize_window(t_mlx_data *s_window);
static void	ft_set_hooks(t_fdf *s_fdf);

int	main(int argc, char **argv)
{
	t_fdf	s_fdf;

	if (argc != 2)
	{
		errno = 22;
		perror("ERROR");
		exit(EXIT_FAILURE);
	}
	ft_set_fdf_data(&s_fdf, argv[1]);
	ft_parse_map(&s_fdf);
	ft_initialize_window(&(s_fdf.s_mlx_data));
	ft_print_map(&s_fdf);
	mlx_put_image_to_window(s_fdf.s_mlx_data.mlx_ptr, s_fdf.s_mlx_data.win_ptr, \
			s_fdf.s_mlx_data.s_img.img, 0, 0);
	ft_print_help(&s_fdf);
	ft_set_hooks(&s_fdf);
	mlx_loop(s_fdf.s_mlx_data.mlx_ptr);
	return (0);
}

void	ft_set_fdf_data(t_fdf *s_fdf, char *path)
{
	s_fdf->s_file_data.path = path;
	s_fdf->s_isometric_data.interspace = 20;
	s_fdf->s_isometric_data.height = 3;
	s_fdf->s_isometric_data.angle = ft_rad(30);
	s_fdf->s_isometric_data.origin_x = WINDOW_WIDTH / 2;
	s_fdf->s_isometric_data.origin_y = 100;
	s_fdf->s_isometric_data.move_x = s_fdf->s_isometric_data.origin_x;
	s_fdf->s_isometric_data.move_y = s_fdf->s_isometric_data.origin_y;
	s_fdf->mode = NORMAL_MODE;
	s_fdf->toggle_menu = true;
	s_fdf->drag_drop_status = false;
	s_fdf->exit_status = EXIT_SUCCESS;
}

static void	ft_initialize_window(t_mlx_data *s_window)
{
	s_window->mlx_ptr = mlx_init();
	if (s_window->mlx_ptr == NULL)
		exit(EXIT_FAILURE);
	s_window->win_ptr = mlx_new_window(s_window->mlx_ptr, \
			WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
	if (s_window->win_ptr == NULL)
	{
		free(s_window->win_ptr);
		exit(EXIT_FAILURE);
	}
	s_window->s_img.img = mlx_new_image(s_window->mlx_ptr, \
			WINDOW_WIDTH, WINDOW_HEIGHT);
	if (s_window->s_img.img == NULL)
	{
		free(s_window->win_ptr);
		exit(EXIT_FAILURE);
	}
	s_window->s_img.addr = mlx_get_data_addr(s_window->s_img.img, \
			&s_window->s_img.bpp, &s_window->s_img.line_len, \
			&s_window->s_img.endian);
}

static void	ft_set_hooks(t_fdf *s_fdf)
{
	mlx_key_hook(s_fdf->s_mlx_data.win_ptr, &ft_key_pressed, s_fdf);
	mlx_mouse_hook(s_fdf->s_mlx_data.win_ptr, &ft_mouse_scroll, s_fdf);
	mlx_hook(s_fdf->s_mlx_data.win_ptr, ON_DESTROY, 0, &ft_close, s_fdf);
	mlx_hook(s_fdf->s_mlx_data.win_ptr, ON_KEYDOWN, 0, &ft_hold_key, s_fdf);
	mlx_hook(s_fdf->s_mlx_data.win_ptr, ON_MOUSEUP, 0, &ft_mouse_release, s_fdf);
	mlx_hook(s_fdf->s_mlx_data.win_ptr, ON_MOUSEMOVE, 0, &ft_mouse_move, s_fdf);
}
