/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:22:59 by shinfray          #+#    #+#             */
/*   Updated: 2023/01/09 16:36:15 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_free_all(char **line, char **buf)
{
	if (line != NULL && *line != NULL)
	{
		free(*line);
		*line = NULL;
	}
	if (buf != NULL && *buf != NULL)
	{
		free(*buf);
		*buf = NULL;
	}
	return (NULL);
}

static char	*ft_save_in_cache(char **line, char **str, char *newline_pos)
{
	const size_t	len_str = ft_gnl_strlen(*str);
	size_t			n;
	size_t			i;
	char			*cache;

	n = (newline_pos - *str) + 1;
	i = 0;
	cache = NULL;
	*line = ft_gnl_strnjoin(line, *str, n);
	if (*line == NULL || n == len_str)
		return (ft_free_all(NULL, str));
	cache = ft_calloc(len_str - n + 1, sizeof(*cache));
	if (cache == NULL)
		return (ft_free_all(line, str));
	while ((*str)[n] != '\0')
		cache[i++] = (*str)[n++];
	ft_free_all(NULL, str);
	return (cache);
}

static char	*ft_parser(int fd, char **line)
{
	ssize_t	bytes_read;
	char	*buf;
	char	*newline_pos;

	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(*buf));
	if (buf == NULL)
		return (ft_free_all(line, NULL));
	bytes_read = read(fd, buf, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buf[bytes_read] = '\0';
		newline_pos = ft_strchr(buf, '\n');
		if (newline_pos != NULL)
			return (ft_save_in_cache(line, &buf, newline_pos));
		*line = ft_gnl_strnjoin(line, buf, bytes_read);
		if (*line == NULL)
			return (ft_free_all(NULL, &buf));
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	if (bytes_read < 0)
		return (ft_free_all(line, &buf));
	return (ft_free_all(NULL, &buf));
}

static char	ft_retrieve_from_cache(char **cache, char **line)
{
	char	*newline_pos;

	if (*cache == NULL)
		return (NEWLINE_NOT_FOUND);
	newline_pos = ft_strchr(*cache, '\n');
	if (newline_pos != NULL)
	{
		*cache = ft_save_in_cache(line, cache, newline_pos);
		return (NEWLINE_FOUND);
	}
	*line = ft_gnl_strnjoin(cache, NULL, BUFFER_SIZE);
	if (*line == NULL)
		return (ERROR);
	return (NEWLINE_NOT_FOUND);
}

char	*get_next_line(int fd)
{
	static char	*cache[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	line = NULL;
	if (ft_retrieve_from_cache(&cache[fd], &line) == NEWLINE_NOT_FOUND)
		cache[fd] = ft_parser(fd, &line);
	return (line);
}
