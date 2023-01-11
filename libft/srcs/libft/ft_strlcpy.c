/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:35:19 by shinfray          #+#    #+#             */
/*   Updated: 2022/10/17 02:40:56 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	const char *const	ptr = src;

	if (dstsize == 0 || (dst == NULL || src == NULL))
		return (ft_strlen(src));
	while (*src != '\0' && --dstsize != 0)
		*dst++ = *src++;
	*dst = '\0';
	if (dstsize == 0)
	{
		while (*src != '\0')
			++src;
	}
	return (src - ptr);
}
