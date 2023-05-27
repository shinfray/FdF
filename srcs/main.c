/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:44:59 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/27 03:16:09 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	s_fdf;

	errno = 0;
	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./fdf MAP_FILE", 2);
		exit(EXIT_FAILURE);
	}
	ft_set_fdf_data(&s_fdf, argv[1]);
	ft_initialize_window(&(s_fdf.s_mlx_data));
	ft_parse_map(&s_fdf);
	ft_print_map(&s_fdf);
	ft_set_hooks(&s_fdf);
	mlx_loop(s_fdf.s_mlx_data.mlx_ptr);
	return (0);
}
