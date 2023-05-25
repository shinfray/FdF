/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:44:59 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/25 17:13:25 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	s_fdf;

	if (argc != 2)
	{
		errno = EINVAL;
		perror("ERROR");
		exit(EXIT_FAILURE);
	}
	ft_set_fdf_data(&s_fdf, argv[1]);
	ft_parse_map(&s_fdf);
	ft_initialize_window(&(s_fdf.s_mlx_data));
	ft_print_map(&s_fdf);
	ft_set_hooks(&s_fdf);
	mlx_loop(s_fdf.s_mlx_data.mlx_ptr);
	return (0);
}
