/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:23:48 by shinfray          #+#    #+#             */
/*   Updated: 2023/01/09 16:36:00 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*cast_dst;
	const char	*cast_src;

	cast_dst = (char *)dst;
	cast_src = (const char *)src;
	if (n == 0 || cast_src == cast_dst)
		return (dst);
	while (n--)
		*cast_dst++ = *cast_src++;
	return (dst);
}

size_t	ft_gnl_strlen(const char *str)
{
	const char *const	ptr = str;

	if (str == NULL)
		return (0);
	while (*str != '\0')
		++str;
	return (str - ptr);
}

void	*ft_calloc(size_t count, size_t size)
{
	const size_t	full_size = size * count;
	size_t			i;
	char			*ptr;

	i = 0;
	ptr = malloc(full_size);
	if (ptr != NULL)
	{
		while (i < full_size)
			ptr[i++] = '\0';
	}
	return (ptr);
}

char	*ft_gnl_strnjoin(char **s1, char const *s2, size_t n)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str;

	s1_len = ft_gnl_strlen(*s1);
	s2_len = ft_gnl_strlen(s2);
	if (n < s2_len)
		s2_len = n;
	str = ft_calloc(s1_len + s2_len + 1, sizeof(*str));
	if (str != NULL)
	{
		ft_memcpy(str, *s1, s1_len);
		ft_memcpy(str + s1_len, s2, s2_len);
	}
	if (s1 != NULL && *s1 != NULL)
		free(*s1);
	*s1 = NULL;
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	const char	c2 = c;

	while (*s != c2)
	{
		if (*s++ == '\0')
			return (NULL);
	}
	return ((char *)s);
}
