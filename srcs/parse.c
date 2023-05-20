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
	map_data->map = ft_calloc(array_size, sizeof(*(map_data->map)));
	if (map_data->map == NULL)
		ft_print_error_and_exit();
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_print_error_and_exit();
	i = 0;
	x = 0;
	y = 0;
	row = ft_split(get_next_line(fd), " \n");
	while (row != NULL)
	{
		while (row[j] != NULL)
		{
			map_data->map[i].x = x;
			map_data->map[i].y = y;
			map_data->map[i].z = ft_atoi(row[j]);
			map_data->map[i].color = 0x00FF00; 
			++x;
			++i;
			++j;
		}
		ft_free_row(row);
		x = 0;
		++y;
		j = 0;
		row = ft_split(get_next_line(fd), " \n");
	}
	close(fd);
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
	row = ft_split(get_next_line(fd), " \n");
	if (row == NULL)
		{
			close(fd);
			ft_print_error_and_exit();
		}
	map_data->total_column = ft_array_of_string_len((const char **)row);
	while (row != NULL)
	{
		// 1er calcul inutile
		if (map_data->total_column != ft_array_of_string_len((const char **)row))
		{
			ft_free_row(row);
			errno = EFTYPE;
			return (-1);
		}
		ft_free_row(row);
		++(map_data->total_row);
		row = ft_split(get_next_line(fd), " \n");
	}
	return (map_data->total_column * map_data->total_row);
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