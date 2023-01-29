/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 19:08:25 by shinfray          #+#    #+#             */
/*   Updated: 2023/01/27 00:59:28 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*cast_dst;
	const char	*cast_src;

	cast_dst = (char *)dst;
	cast_src = (const char *)src;
	if (cast_src == cast_dst)
		return (dst);
	while (n-- > 0)
		*cast_dst++ = *cast_src++;
	return (dst);
}

size_t	ft_gnl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		++i;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	const size_t	full_size = size * count;
	size_t			i;
	char			*ptr;

	i = 0;
	ptr = malloc(full_size);
	if (ptr != NULL)
		while (i < full_size)
			ptr[i++] = '\0';
	return (ptr);
}

char	*ft_gnl_strnjoin(char *s1, const char *s2, size_t n_from_s2_to_copy)
{
	size_t	s1_len;
	char	*dest_str;

	if (s1 != NULL)
		s1_len = ft_gnl_strlen(s1);
	else
		s1_len = 0;
	dest_str = ft_calloc(s1_len + n_from_s2_to_copy + 1, sizeof(*dest_str));
	if (dest_str != NULL)
	{
		ft_memcpy(dest_str, s1, s1_len);
		ft_memcpy(dest_str + s1_len, s2, n_from_s2_to_copy);
	}
	if (s1 != NULL)
		free(s1);
	return (dest_str);
}

char	*ft_gnl_strchr(const char *s)
{
	while (*s != '\n' && *s != '\0')
			++s;
	return ((char *)s);
}
