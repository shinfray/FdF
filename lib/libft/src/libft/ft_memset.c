/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:23:36 by shinfray          #+#    #+#             */
/*   Updated: 2022/10/21 01:51:48 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	const unsigned char	uc_c = c;
	unsigned char		*uc_b;

	if (len != 0)
	{
		uc_b = (unsigned char *)b;
		while (len-- != 0)
			*uc_b++ = uc_c;
	}
	return (b);
}
