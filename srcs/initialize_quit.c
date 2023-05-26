/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_quit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:57:21 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/26 04:13:31 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_set_fdf_data(t_fdf *s_fdf, char *path);
void	ft_initialize_window(t_mlx_data *mlx_data);
void	ft_set_hooks(t_fdf *s_fdf);
double	ft_rad(int degree);
int		ft_clean_quit(t_fdf *s_fdf);

void	ft_set_fdf_data(t_fdf *s_fdf, char *path)
{
	s_fdf->s_file_data.path = path;
	s_fdf->s_isometric_data.interspace = INTERSPACE;
	s_fdf->s_isometric_data.height = INTERSPACE;
	s_fdf->s_isometric_data.angle_x = asin(tan(ft_rad(30)));
	s_fdf->s_isometric_data.angle_y = ft_rad(0);
	s_fdf->s_isometric_data.angle_z = ft_rad(45);
	s_fdf->s_isometric_data.move_x = WINDOW_WIDTH / 2;
	s_fdf->s_isometric_data.move_y = WINDOW_HEIGHT / 8;
	s_fdf->mode = NORMAL_MODE;
	s_fdf->toggle_menu = true;
	s_fdf->drag_drop_status = false;
	s_fdf->exit_status = EXIT_SUCCESS;
}

void	ft_initialize_window(t_mlx_data *mlx_data)
{
	mlx_data->mlx_ptr = mlx_init();
	if (mlx_data->mlx_ptr == NULL)
		exit(EXIT_FAILURE);
	mlx_data->win_ptr = mlx_new_window(mlx_data->mlx_ptr, \
		WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
	if (mlx_data->win_ptr == NULL)
		exit(EXIT_FAILURE);
	mlx_data->s_img.img = mlx_new_image(mlx_data->mlx_ptr, \
		WINDOW_WIDTH, WINDOW_HEIGHT);
	if (mlx_data->s_img.img == NULL)
	{
		mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->win_ptr);
		exit(EXIT_FAILURE);
	}
	mlx_data->s_img.addr = mlx_get_data_addr(mlx_data->s_img.img, \
		&mlx_data->s_img.bpp, &mlx_data->s_img.line_len, \
		&mlx_data->s_img.endian);
}

void	ft_set_hooks(t_fdf *s_fdf)
{
	mlx_key_hook(s_fdf->s_mlx_data.win_ptr, &ft_key_pressed, s_fdf);
	mlx_mouse_hook(s_fdf->s_mlx_data.win_ptr, &ft_click, s_fdf);
	mlx_hook(s_fdf->s_mlx_data.win_ptr, ON_DESTROY, 0, &ft_clean_quit, s_fdf);
	mlx_hook(s_fdf->s_mlx_data.win_ptr, ON_KEYDOWN, 0, &ft_hold_key, s_fdf);
	mlx_hook(s_fdf->s_mlx_data.win_ptr, ON_MOUSEUP, 0, &ft_unclick, s_fdf);
	mlx_hook(s_fdf->s_mlx_data.win_ptr, ON_MOUSEMOVE, 0, &ft_move_mouse, s_fdf);
}

double	ft_rad(int degree)
{
	return ((double)degree * (M_PI / 180.0));
}

int	ft_clean_quit(t_fdf *s_fdf)
{
	mlx_destroy_image(s_fdf->s_mlx_data.mlx_ptr, s_fdf->s_mlx_data.s_img.img);
	mlx_destroy_window(s_fdf->s_mlx_data.mlx_ptr, s_fdf->s_mlx_data.win_ptr);
	free(s_fdf->s_mlx_data.mlx_ptr);
	free(s_fdf->s_map_data.s_map);
	if (s_fdf->exit_status == EXIT_FAILURE)
		perror("ERROR");
	exit(s_fdf->exit_status);
}
