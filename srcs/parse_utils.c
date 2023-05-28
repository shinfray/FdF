/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 02:53:14 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/28 10:22:12 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

ssize_t		ft_check_file_format_and_map_size(t_fdf *s_fdf);
char		*ft_free_row(char **row);
static bool	ft_check_file_extension(const char *path);
static bool	ft_check_number_column(int total_column_first_row, char **row);
static int	ft_array_of_str_len(char **array);

ssize_t	ft_check_file_format_and_map_size(t_fdf *s_fdf)
{
	char	**row;

	if (ft_check_file_extension(s_fdf->s_file.path) == 1)
		return (-1);
	s_fdf->s_file.fd = open(s_fdf->s_file.path, O_RDONLY);
	if (s_fdf->s_file.fd == -1)
		return (-1);
	row = ft_split(get_next_line(s_fdf->s_file.fd), " \n");
	if (row == NULL)
		return (-1);
	s_fdf->s_map.total_row = 0;
	s_fdf->s_map.total_column = ft_array_of_str_len(row);
	while (row != NULL)
	{
		ft_free_row(row);
		++(s_fdf->s_map.total_row);
		row = ft_split(get_next_line(s_fdf->s_file.fd), " \n");
		if (ft_check_number_column(s_fdf->s_map.total_column, row) == 1)
			return (-1);
	}
	close(s_fdf->s_file.fd);
	return (s_fdf->s_map.total_column * s_fdf->s_map.total_row);
}

char	*ft_free_row(char **row)
{
	char	**ptr;

	ptr = row;
	while (*row != NULL)
		free(*row++);
	free(ptr);
	return (NULL);
}

static bool	ft_check_file_extension(const char *path)
{
	const char		*file_extension;
	const size_t	file_length = ft_strlen(path);

	file_extension = ft_strnstr(path, ".fdf", file_length);
	if (file_extension == NULL || file_extension[4] != '\0' \
		|| file_extension == path)
	{
		errno = EFTYPE;
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
