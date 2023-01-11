/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 21:19:02 by shinfray          #+#    #+#             */
/*   Updated: 2023/01/09 16:41:03 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define ERROR				-1
# define NEWLINE_NOT_FOUND	0
# define NEWLINE_FOUND		1

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

char	*get_next_line(int fd);
size_t	ft_gnl_strlen(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_gnl_strnjoin(char **s1, char const *s2, size_t n);
char	*ft_strchr(const char *s, int c);

#endif
