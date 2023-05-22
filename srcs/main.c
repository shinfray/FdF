/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:44:59 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/22 13:34:46 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_initialize_fdf_data(t_fdf *s_fdf, char *path);
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
	ft_initialize_fdf_data(&s_fdf, argv[1]);
	ft_parse_map(&s_fdf);
	ft_initialize_window(&(s_fdf.mlx_data));
	ft_print_map(&s_fdf);
	//ft_draw_rectangle(&s_window.s_img, (t_rect){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFFFFFF});
	//ft_draw_line(&s_window.s_img, (t_point){483, 46, 0, 0x00FF0000, 0}, (t_point){12, 72, 0, 0x00FF0000, 0});
	mlx_put_image_to_window(s_fdf.mlx_data.mlx_ptr, s_fdf.mlx_data.win_ptr, \
			s_fdf.mlx_data.s_img.img, 0, 0);
	ft_print_help(&s_fdf);
	ft_set_hooks(&s_fdf);
	mlx_loop(s_fdf.mlx_data.mlx_ptr);
	return (0);
}

static void	ft_initialize_fdf_data(t_fdf *s_fdf, char *path)
{
	s_fdf->s_file_data.fd = -1;
	s_fdf->s_file_data.path = path;
	s_fdf->s_isometric_data.interspace = 10;
	s_fdf->s_isometric_data.height = 3;
	s_fdf->s_isometric_data.angle = ft_rad(30);
	s_fdf->s_isometric_data.origin_x = 200;
	s_fdf->s_isometric_data.origin_y = 200;
	s_fdf->s_isometric_data.move_x = 0;
	s_fdf->s_isometric_data.move_y = 0;
	s_fdf->map_data.map = NULL;
	s_fdf->mode = NORMAL_MODE;
	s_fdf->toggle_menu = true;
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
	//mlx_mouse_hook(s_fdf->mlx_data.win_ptr, &ft_mouse_click, s_fdf);
	mlx_key_hook(s_fdf->mlx_data.win_ptr, &ft_key_pressed, s_fdf);
	mlx_mouse_hook(s_fdf->mlx_data.win_ptr, &ft_mouse_scroll, s_fdf);
	mlx_hook(s_fdf->mlx_data.win_ptr, ON_DESTROY, 0, &ft_close, s_fdf);
	mlx_hook(s_fdf->mlx_data.win_ptr, ON_KEYDOWN, 0, &ft_hold_key, s_fdf);
}

void	ft_print_help(t_fdf *s_fdf)
{
	if (s_fdf->toggle_menu == false)
		return ;
	mlx_string_put(s_fdf->mlx_data.mlx_ptr, s_fdf->mlx_data.win_ptr, \
			10, 10, 0xFFFFFF, "N: NORMAL MODE");
	mlx_string_put(s_fdf->mlx_data.mlx_ptr, s_fdf->mlx_data.win_ptr, \
			10, 30, 0xFFFFFF, "Z: ZOOM MODE");
	mlx_string_put(s_fdf->mlx_data.mlx_ptr, s_fdf->mlx_data.win_ptr, \
			10, 50, 0xFFFFFF, "R: ROTATE MODE");
	mlx_string_put(s_fdf->mlx_data.mlx_ptr, s_fdf->mlx_data.win_ptr, \
			10, 70, 0xFFFFFF, "H: HEIGHT MODE");
	mlx_string_put(s_fdf->mlx_data.mlx_ptr, s_fdf->mlx_data.win_ptr, \
			10, 90, 0xFFFFFF, "USE ARROW KEYS");
	mlx_string_put(s_fdf->mlx_data.mlx_ptr, s_fdf->mlx_data.win_ptr, \
			10, 110, 0xFFFFFF, "M: TOGGLE HELP MENU");
}
