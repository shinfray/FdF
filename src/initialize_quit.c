/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_quit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:57:21 by shinfray          #+#    #+#             */
/*   Updated: 2023/06/01 11:46:38 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_set_fdf_data(t_fdf *s_fdf, char *path);
void	ft_initialize_window(t_mlx *mlx_data);
void	ft_set_hooks(t_fdf *s_fdf);
double	ft_rad(int degree);
int		ft_clean_quit(t_fdf *s_fdf);

void	ft_set_fdf_data(t_fdf *s_fdf, char *path)
{
	s_fdf->s_file.path = path;
	s_fdf->s_isometric.interspace = INTERSPACE;
	s_fdf->s_isometric.height = INTERSPACE;
	s_fdf->s_isometric.angle_x = ft_rad(45);
	s_fdf->s_isometric.angle_y = asin(tan(ft_rad(30)));
	s_fdf->s_isometric.angle_z = ft_rad(-30);
	s_fdf->s_isometric.move_x = WINDOW_WIDTH / 4;
	s_fdf->s_isometric.move_y = WINDOW_HEIGHT / 2;
	s_fdf->mode = NORMAL_MODE;
	s_fdf->toggle_menu = true;
	s_fdf->drag_drop_status = false;
	s_fdf->exit_status = EXIT_SUCCESS;
}

void	ft_initialize_window(t_mlx *mlx_data)
{
	mlx_data->mlx_ptr = mlx_init();
	if (mlx_data->mlx_ptr != NULL)
	{
		mlx_data->win_ptr = mlx_new_window(mlx_data->mlx_ptr, \
			WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
		if (mlx_data->win_ptr != NULL)
		{
			mlx_data->s_img.img = mlx_new_image(mlx_data->mlx_ptr, \
				WINDOW_WIDTH, WINDOW_HEIGHT);
			if (mlx_data->s_img.img != NULL)
			{
				mlx_data->s_img.addr = mlx_get_data_addr(mlx_data->s_img.img, \
					&mlx_data->s_img.bpp, &mlx_data->s_img.line_len, \
					&mlx_data->s_img.endian);
				return ;
			}
			mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->win_ptr);
		}
	}
	ft_putendl_fd("Window initialization error", 2);
	exit(EXIT_FAILURE);
}

void	ft_set_hooks(t_fdf *s_fdf)
{
	mlx_key_hook(s_fdf->s_mlx.win_ptr, &ft_key_pressed, s_fdf);
	mlx_mouse_hook(s_fdf->s_mlx.win_ptr, &ft_click, s_fdf);
	mlx_hook(s_fdf->s_mlx.win_ptr, ON_DESTROY, 0, &ft_clean_quit, s_fdf);
	mlx_hook(s_fdf->s_mlx.win_ptr, ON_KEYDOWN, 0, &ft_hold_key, s_fdf);
	mlx_hook(s_fdf->s_mlx.win_ptr, ON_MOUSEUP, 0, &ft_unclick, s_fdf);
	mlx_hook(s_fdf->s_mlx.win_ptr, ON_MOUSEMOVE, 0, &ft_move_mouse, s_fdf);
}

double	ft_rad(int degree)
{
	return ((double)degree * (M_PI / 180.0));
}

int	ft_clean_quit(t_fdf *s_fdf)
{
	mlx_destroy_image(s_fdf->s_mlx.mlx_ptr, s_fdf->s_mlx.s_img.img);
	mlx_destroy_window(s_fdf->s_mlx.mlx_ptr, s_fdf->s_mlx.win_ptr);
	free(s_fdf->s_map.s_map_addr);
	if (s_fdf->exit_status == EXIT_FAILURE && errno != 0)
		perror("ERROR");
	exit(s_fdf->exit_status);
}
