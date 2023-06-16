/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:35:08 by shinfray          #+#    #+#             */
/*   Updated: 2022/10/21 02:35:09 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_isset(char const *set, char const c)
{
	while (*set != '\0' && *set != c)
		++set;
	return (*set == c);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	char	*dest;
	size_t	dest_len;

	ptr = NULL;
	dest = NULL;
	dest_len = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (ft_isset(set, *s1) != 0 && *s1 != '\0')
		++s1;
	if (*s1 != '\0')
	{
		ptr = (char *)(s1 + ft_strlen(s1) - 1);
		while (ft_isset(set, *ptr) != 0 && ptr > s1)
			--ptr;
		dest_len = ptr - s1 + 1;
	}
	dest = ft_calloc(dest_len + 1, sizeof(*dest));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s1, dest_len + 1);
	return (dest);
}
