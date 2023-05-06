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

static ssize_t	ft_map_size(int fd, t_map_data *map_data);
static int	ft_array_of_string_len(const char **array);
static char	*ft_free_row(char **row);
static void	ft_print_error_and_exit(void);

void	ft_parse_map(char *file, t_map_data *map_data)
{
	t_point	*map;
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
	array_size = ft_map_size(fd, map_data);
	close(fd);
	if (array_size == -1)
		ft_print_error_and_exit();
	map = ft_calloc(array_size, sizeof(*map_data));
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
			map[i].x = x;
			map[i].y = y;
			map[i].z = ft_atoi(row[j]);
			if (array_size-- > 1)
				map[i].last_point = 0;
			else
				map[i].last_point = 1;
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
	map_data->map = map;
}

static void	ft_print_error_and_exit(void)
{
	perror("ERROR");
	exit(EXIT_FAILURE);
}

static ssize_t	ft_map_size(int fd, t_map_data *map_data)
{
	char	**row;

	map_data->total_row = 0;
	row = ft_split(get_next_line(fd), ' ');
	if (row == NULL)
		{
			close(fd);
			perror("ERROR");
			exit(EXIT_FAILURE);
		}
	map_data->total_column = ft_array_of_string_len((const char **)row);
	while (row != NULL)
	{
		if (map_data->total_column != 0 && map_data->total_column != ft_array_of_string_len((const char **)row))
		{
			ft_free_row(row);
			errno = EFTYPE;
			return (-1);
		}
		ft_free_row(row);
		++(map_data->total_row);
		row = ft_split(get_next_line(fd), ' ');
	}
	return (map_data->total_column * map_data->total_row);
}

static int	ft_array_of_string_len(const char **array)
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