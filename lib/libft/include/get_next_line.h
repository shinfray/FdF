/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:42:58 by shinfray          #+#    #+#             */
/*   Updated: 2023/05/05 12:19:53 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*ft_gnl_strnjoin(char *s1, const char *s2, size_t n_from_s2_to_copy);
char	*ft_gnl_strchr(const char *s);
void	*ft_gnl_calloc(size_t count, size_t size);
size_t	ft_gnl_strlen(const char *str);

#endif
