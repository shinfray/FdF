/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 19:02:04 by shinfray          #+#    #+#             */
/*   Updated: 2022/10/21 01:46:40 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	c2 = c;
	const unsigned char	*ptr;

	if (n != 0)
	{
		ptr = (const unsigned char *)s;
		while (n-- != 0)
		{
			if (*ptr == c2)
				return ((void *)ptr);
			++ptr;
		}
	}
	return (NULL);
}
