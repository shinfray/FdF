/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:46:13 by shinfray          #+#    #+#             */
/*   Updated: 2022/10/18 18:50:15 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	const size_t	f_size = size * count;
	void			*ptr;

	ptr = malloc(f_size);
	if (ptr != NULL)
		ft_memset(ptr, 0, f_size);
	return (ptr);
}
