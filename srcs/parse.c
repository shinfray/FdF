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

t_point	*ft_parse_map(char *file)
{
	t_point	*map_data;
	int		fd;
	char	**row;
	int		x;
	int		y;
	int		i;
	int		j;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		{
			perror("ERROR");
			exit(EXIT_FAILURE);
		}
	
	j = 0;

	/* fonction à boucler */
	row = ft_split(get_next_line(fd), ' ');
	// protéger row
	map_data = ft_calloc(ft_strlen(row), sizeof(*map_data));
	if (map_data == NULL)
		{
			close(fd);
			perror("ERROR");
			exit(EXIT_FAILURE);
		}
	x = 0;
	y = 0;
	i = 0;
	while (row[i] != NULL)
	{
		map_data[j].x = x++;
		map_data[j].y = y;
		map_data[j++].z = ft_atoi(row[i++]);
	}
	free(row);
	x = 0;
	++y;
	i = 0;

	close(fd);
	return (NULL);
}