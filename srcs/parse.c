/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 17:43:39 by shinfray          #+#    #+#             */
/*   Updated: 2023/04/29 18:594:74y shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static ssize_t	ft_map_size(int fd);
static size_t	ft_array_of_string_len(const char **array);
static char	*ft_free_row(char **row);
static void	ft_print_error_and_exit(void);

t_point	*ft_parse_map(char *file)
{
	t_point	*map_data;
	int		fd;
	ssize_t	array_size;
	char	**row;
	int		x;
	int		y;
	int		i;
	int		j;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_print_error_and_exit();
	array_size = ft_map_size(fd);
	close(fd);
	if (array_size == -1)
		ft_print_error_and_exit();
	map_data = ft_calloc(array_size, sizeof(*map_data));
	if (map_data == NULL)
		ft_print_error_and_exit();
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_print_error_and_exit();
	i = 0;
	x = 0;
	y = 0;
	row = ft_split(get_next_line(fd), ' ');
	while (row != NULL)
	{
		while (row[j] != NULL)
		{
			map_data[i].x = x;
			map_data[i].y = y;
			map_data[i].z = ft_atoi(row[j]);
			if (array_size-- > 1)
				map_data[i].last_point = 0;
			else
				map_data[i].last_point = 1;
			++x;
			++i;
			++j;
		}
		ft_free_row(row);
		x = 0;
		++y;
		j = 0;
		row = ft_split(get_next_line(fd), ' ');
	}
	close(fd);
	return (map_data);
}

static void	ft_print_error_and_exit(void)
{
	perror("ERROR");
	exit(EXIT_FAILURE);
}

static ssize_t	ft_map_size(int fd)
{
	char	**row;
	size_t		total_column;
	size_t		total_row;

	total_row = 0;
	row = ft_split(get_next_line(fd), ' ');
	if (row == NULL)
		{
			close(fd);
			perror("ERROR");
			exit(EXIT_FAILURE);
		}
	total_column = ft_array_of_string_len((const char **)row);
	while (row != NULL)
	{
		if (total_column != 0 && total_column != ft_array_of_string_len((const char **)row))
		{
			ft_free_row(row);
			errno = EFTYPE;
			return (-1);
		}
		ft_free_row(row);
		++total_row;
		row = ft_split(get_next_line(fd), ' ');
	}
	return (total_column * total_row);
}

static size_t	ft_array_of_string_len(const char **array)
{
	const char	**ptr;

	if (array == NULL)
		return (0);
	ptr = array;
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