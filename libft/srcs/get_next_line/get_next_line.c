/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 14:50:45 by shinfray          #+#    #+#             */
/*   Updated: 2023/01/29 23:30:50 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free(char **ptr)
{
	if (*ptr != NULL)
		free(*ptr);
	*ptr = NULL;
	return (NULL);
}

static char	*ft_update_stash(char *line, char **stash, char *newline)
{
	char	*temp;

	line = ft_gnl_strnjoin(line, *stash, newline - *stash + 1);
	if (line == NULL)
		return (ft_free(stash));
	++newline;
	if (*newline == '\0')
	{
		ft_free(stash);
		return (line);
	}
	temp = ft_gnl_strnjoin(NULL, newline, ft_gnl_strlen(newline));
	ft_free(stash);
	if (temp == NULL)
		return (ft_free(&line));
	*stash = temp;
	return (line);
}

static char	*ft_parse(int fd, char *line, char **stash)
{
	ssize_t	bytes_read;
	char	*newline;

	*stash = ft_calloc(BUFFER_SIZE + 1, sizeof(**stash));
	if (*stash == NULL)
		return (ft_free(&line));
	bytes_read = read(fd, *stash, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		(*stash)[bytes_read] = '\0';
		newline = ft_gnl_strchr(*stash);
		if (*newline == '\n')
			return (ft_update_stash(line, stash, newline));
		line = ft_gnl_strnjoin(line, *stash, newline - *stash);
		if (line == NULL)
			return (ft_free(stash));
		bytes_read = read(fd, *stash, BUFFER_SIZE);
	}
	ft_free(stash);
	if (bytes_read < 0)
		return (ft_free(&line));
	return (line);
}

static char	*ft_retrieve_from_stash(int fd, char *line, char **stash)
{
	char	*newline;

	newline = ft_gnl_strchr(*stash);
	if (*newline == '\n')
		return (ft_update_stash(line, stash, newline));
	line = ft_gnl_strnjoin(NULL, *stash, newline - *stash);
	ft_free(stash);
	if (line == NULL)
		return (NULL);
	return (ft_parse(fd, line, stash));
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	line = NULL;
	if (stash != NULL)
		return (ft_retrieve_from_stash(fd, line, &stash));
	else
		return (ft_parse(fd, line, &stash));
}
