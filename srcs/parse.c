/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 03:41:30 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/28 10:22:12 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			ft_parse_map(t_fdf *s_fdf);
static void		ft_fill_array(t_fdf *s_fdf);

void	ft_parse_map(t_fdf *s_fdf)
{
	s_fdf->s_map.s_map_addr = NULL;
	s_fdf->s_map.total_size = ft_check_file_format_and_map_size(s_fdf);
	if (s_fdf->s_map.total_size != -1)
	{
		s_fdf->s_map.s_map_addr = ft_calloc(s_fdf->s_map.total_size, \
				sizeof(*(s_fdf->s_map.s_map_addr)));
		if (s_fdf->s_map.s_map_addr != NULL)
		{
			s_fdf->s_file.fd = open(s_fdf->s_file.path, O_RDONLY);
			if (s_fdf->s_file.fd != -1)
			{
				ft_fill_array(s_fdf);
				close(s_fdf->s_file.fd);
				return ;
			}
		}
	}
	s_fdf->exit_status = EXIT_FAILURE;
	ft_putendl_fd("Map initialization error", 2);
	ft_clean_quit(s_fdf);
}

static void	ft_fill_array(t_fdf *s_fdf)
{
	char	**row;
	int		column_n;
	int		row_n;
	int		i;

	i = 0;
	column_n = 0;
	row_n = 0;
	row = ft_split(get_next_line(s_fdf->s_file.fd), " \n");
	while (row != NULL)
	{
		while (column_n < s_fdf->s_map.total_column)
		{
			s_fdf->s_map.s_map_addr[i].x = column_n;
			s_fdf->s_map.s_map_addr[i].y = row_n;
			s_fdf->s_map.s_map_addr[i].z = ft_atoi(row[column_n++]);
			s_fdf->s_map.s_map_addr[i++].colour = DEFAULT_COLOUR;
		}
		ft_free_row(row);
		column_n = 0;
		++row_n;
		row = ft_split(get_next_line(s_fdf->s_file.fd), " \n");
	}
}
