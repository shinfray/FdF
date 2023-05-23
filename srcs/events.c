/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 03:40:45 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/23 17:17:27 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_reset(t_fdf *s_fdf);

void	ft_reset(t_fdf *s_fdf)
{
	ft_set_fdf_data(s_fdf, s_fdf->s_file_data.path);
	ft_reprint_image(s_fdf);
}

int	ft_close(t_fdf *s_fdf)
{
	mlx_destroy_image(s_fdf->s_mlx_data.mlx_ptr, s_fdf->s_mlx_data.s_img.img);
	mlx_destroy_window(s_fdf->s_mlx_data.mlx_ptr, s_fdf->s_mlx_data.win_ptr);
	free(s_fdf->s_mlx_data.mlx_ptr);
	if (s_fdf->s_map_data.s_map != NULL)
		free(s_fdf->s_map_data.s_map);
	exit(s_fdf->exit_status);
}

void	ft_reprint_image(t_fdf *s_fdf)
{
	void		*backup;

	backup = s_fdf->s_mlx_data.s_img.img;
	s_fdf->s_mlx_data.s_img.img = mlx_new_image(s_fdf->s_mlx_data.mlx_ptr, \
			WINDOW_WIDTH, WINDOW_HEIGHT);
	if (s_fdf->s_mlx_data.s_img.img == NULL)
	{
		s_fdf->s_mlx_data.s_img.img = backup;
		s_fdf->exit_status = EXIT_FAILURE;
		ft_close(s_fdf);
	}
	s_fdf->s_mlx_data.s_img.addr = \
			mlx_get_data_addr(s_fdf->s_mlx_data.s_img.img, \
			&(s_fdf->s_mlx_data.s_img.bpp), \
			&(s_fdf->s_mlx_data.s_img.line_len), \
			&(s_fdf->s_mlx_data.s_img.endian));
	ft_print_map(s_fdf);
	ft_refresh_interface(s_fdf);
	mlx_destroy_image(s_fdf->s_mlx_data.mlx_ptr, backup);
}
