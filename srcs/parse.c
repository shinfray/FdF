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

t_point	*ft_parse_map(char *file)
{
	t_point	*map_data;
	int		fd;
	ssize_t	array_size;
	// char	**row;
	// int		x;
	// int		y;
	// int		i;
	// int		j;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("ERROR");
		exit(EXIT_FAILURE);
	}
	array_size = ft_map_size(fd);
	close(fd);
	if (array_size == -1)
	{
		perror("ERROR");
		exit(EXIT_FAILURE);
	}
	
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("ERROR");
		exit(EXIT_FAILURE);
	}

	// j = 0;

	// row = ft_split(get_next_line(fd), ' ');
	// // protéger row
	// while (row != NULL)
	// {
	// 	map_data = ft_calloc(ft_array_of_string_len((const char **)row) + 1, sizeof(*map_data));
	// 	if (map_data == NULL)
	// 		{
	// 			close(fd);
	// 			perror("ERROR");
	// 			exit(EXIT_FAILURE);
	// 		}
	// 	x = 0;
	// 	y = 0;
	// 	i = 0;
	// 	while (row[i] != NULL)
	// 	{
	// 		map_data[j].x = x++;
	// 		map_data[j].y = y;
	// 		map_data[j++].z = ft_atoi(row[i++]);
	// 	}
	// 	ft_free_row(row);
	// 	x = 0;
	// 	++y;
	// 	i = 0;
	// 	row = ft_split(get_next_line(fd), ' ');
	// 	// protéger row
	// }

	close(fd);
	return (NULL);
}

static ssize_t	ft_map_size(int fd)
{
	const char	**row;
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
	total_column = ft_array_of_string_len(row);
	while (row != NULL)
	{
		if (total_column != 0 && total_column != ft_array_of_string_len(row))
		{
			ft_free_row(row);
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
	while (ptr != NULL)
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