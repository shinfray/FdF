/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 03:41:30 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/25 21:00:50 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			ft_parse_map(t_fdf *s_fdf);
static void		ft_fill_array(t_fdf *s_fdf);

void	ft_parse_map(t_fdf *s_fdf)
{
	s_fdf->s_map_data.total_size = ft_check_file_format_and_map_size(s_fdf);
	if (s_fdf->s_map_data.total_size == -1)
	{
		s_fdf->exit_status = EXIT_FAILURE;
		ft_close(s_fdf);
	}
	s_fdf->s_map_data.s_map = ft_calloc(s_fdf->s_map_data.total_size, \
			sizeof(*(s_fdf->s_map_data.s_map)));
	if (s_fdf->s_map_data.s_map == NULL)
	{
		s_fdf->exit_status = EXIT_FAILURE;
		ft_close(s_fdf);
	}
	s_fdf->s_file_data.fd = open(s_fdf->s_file_data.path, O_RDONLY);
	if (s_fdf->s_file_data.fd == -1)
	{
		s_fdf->exit_status = EXIT_FAILURE;
		ft_close(s_fdf);
	}
	ft_fill_array(s_fdf);
	close(s_fdf->s_file_data.fd);
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
	row = ft_split(get_next_line(s_fdf->s_file_data.fd), " \n");
	while (row_n < s_fdf->s_map_data.total_row)
	{
		while (column_n < s_fdf->s_map_data.total_column)
		{
			s_fdf->s_map_data.s_map[i].x = column_n;
			s_fdf->s_map_data.s_map[i].y = row_n;
			s_fdf->s_map_data.s_map[i].z = ft_atoi(row[column_n++]);
			s_fdf->s_map_data.s_map[i++].colour = DEFAULT_COLOUR;
		}
		ft_free_row(row);
		column_n = 0;
		++row_n;
		row = ft_split(get_next_line(s_fdf->s_file_data.fd), " \n");
	}
}
