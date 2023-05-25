/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 03:41:30 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/25 20:10:30 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			ft_parse_map(t_fdf *s_fdf);
static ssize_t	ft_check_file_and_map_size(t_fdf *s_fdf);
static int		ft_array_of_str_len(char **array);
static char		*ft_free_row(char **row);
static void		ft_print_error_and_exit(void);
static bool		ft_check_number_column(int total_column_first_row, char **row);
static bool		ft_check_file_extension(const char *path);

void	ft_parse_map(t_fdf *s_fdf)
{
	char	**row;
	int		column_n;
	int		row_n;
	int		i;

	s_fdf->s_map_data.total_size = ft_check_file_and_map_size(s_fdf);
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

	close(s_fdf->s_file_data.fd);
}

static void	ft_fill_array(t_fdf *s_fdf)
{

}

static void	ft_print_error_and_exit(void)
{
	perror("ERROR");
	exit(EXIT_FAILURE);
}

static ssize_t	ft_check_file_and_map_size(t_fdf *s_fdf)
{
	char	**row;

	if (ft_check_file_extension(s_fdf->s_file_data.path) == 1)
		return (-1);
	s_fdf->s_file_data.fd = open(s_fdf->s_file_data.path, O_RDONLY);
	if (s_fdf->s_file_data.fd == -1)
		return (-1);
	row = ft_split(get_next_line(s_fdf->s_file_data.fd), " \n");
	if (row == NULL)
		return (-1);
	s_fdf->s_map_data.total_row = 0;
	s_fdf->s_map_data.total_column = ft_array_of_str_len(row);
	while (row != NULL)
	{
		ft_free_row(row);
		++(s_fdf->s_map_data.total_row);
		row = ft_split(get_next_line(s_fdf->s_file_data.fd), " \n");
		if (ft_check_number_column(s_fdf->s_map_data.total_column, row) == 1)
			return (-1);
	}
	close(s_fdf->s_file_data.fd);
	return (s_fdf->s_map_data.total_column * s_fdf->s_map_data.total_row);
}

static bool	ft_check_file_extension(const char *path)
{
	const char		*file_extension;
	const size_t	file_length = ft_strlen(path);

	file_extension = ft_strnstr(path, ".fdf", file_length);
	if (file_extension == NULL || file_extension[4] != '\0' \
		|| file_extension == path)
	{
		errno = EINVAL;
		return (1);
	}
	return (0);
}

static bool	ft_check_number_column(int total_column_first_row, char **row)
{
	if (row != NULL && total_column_first_row != ft_array_of_str_len(row))
	{
		ft_free_row(row);
		errno = EFTYPE;
		return (1);
	}
	return (0);
}

static int	ft_array_of_str_len(char **array)
{
	char	**ptr;

	ptr = array;
	if (ptr == NULL)
		return (-1);
	while (*ptr != NULL)
		++ptr;
	return (ptr - array);
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
