/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 03:41:30 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/22 20:59:31 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static ssize_t	ft_map_size(t_fdf *s_fdf);
static int		ft_array_of_string_len(const char **array);
static char		*ft_free_row(char **row);
static void		ft_print_error_and_exit(void);

void	ft_parse_map(t_fdf *s_fdf)
{
	char	**row;
	int		x;
	int		y;
	int		i;
	int		j;

	s_fdf->s_file_data.fd = open(s_fdf->s_file_data.path, O_RDONLY);
	if (s_fdf->s_file_data.fd == -1)
		ft_print_error_and_exit();
	s_fdf->s_map_data.total_size = ft_map_size(s_fdf);
	close(s_fdf->s_file_data.fd);
	if (s_fdf->s_map_data.total_size == -1)
		ft_print_error_and_exit();
	s_fdf->s_map_data.s_map = ft_calloc(s_fdf->s_map_data.total_size, \
			sizeof(*(s_fdf->s_map_data.s_map)));
	if (s_fdf->s_map_data.s_map == NULL)
		ft_print_error_and_exit();
	s_fdf->s_file_data.fd = open(s_fdf->s_file_data.path, O_RDONLY);
	if (s_fdf->s_file_data.fd == -1)
		ft_print_error_and_exit();
	i = 0;
	x = 0;
	y = 0;
	row = ft_split(get_next_line(s_fdf->s_file_data.fd), " \n");
	while (row != NULL)
	{
		while (row[j] != NULL)
		{
			s_fdf->s_map_data.s_map[i].x = x;
			s_fdf->s_map_data.s_map[i].y = y;
			s_fdf->s_map_data.s_map[i].z = ft_atoi(row[j]);
			s_fdf->s_map_data.s_map[i].colour = 0x00FF00;
			++x;
			++i;
			++j;
		}
		ft_free_row(row);
		x = 0;
		++y;
		j = 0;
		row = ft_split(get_next_line(s_fdf->s_file_data.fd), " \n");
	}
	close(s_fdf->s_file_data.fd);
}

static void	ft_print_error_and_exit(void)
{
	perror("ERROR");
	exit(EXIT_FAILURE);
}

static ssize_t	ft_map_size(t_fdf *s_fdf)
{
	char	**row;

	s_fdf->s_map_data.total_row = 0;
	row = ft_split(get_next_line(s_fdf->s_file_data.fd), " \n");
	if (row == NULL)
	{
		close(s_fdf->s_file_data.fd);
		ft_print_error_and_exit();
	}
	s_fdf->s_map_data.total_column = ft_array_of_string_len((const char **)row);
	while (row != NULL)
	{
		// 1er calcul inutile
		if (s_fdf->s_map_data.total_column \
			!= ft_array_of_string_len((const char **)row))
		{
			ft_free_row(row);
			errno = EFTYPE;
			return (-1);
		}
		ft_free_row(row);
		++(s_fdf->s_map_data.total_row);
		row = ft_split(get_next_line(s_fdf->s_file_data.fd), " \n");
	}
	return (s_fdf->s_map_data.total_column * s_fdf->s_map_data.total_row);
}

static int	ft_array_of_string_len(const char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return (0);
	while (array[i] != NULL)
		++i;
	return (i);
}

static char	*ft_free_row(char **row)
{
	char	**ptr;

	ptr = row;
	while (*row != NULL)
		free(*row++);
	free(ptr);
	return (NULL);
}
