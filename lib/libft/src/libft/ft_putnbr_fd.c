/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:26:06 by shinfray          #+#    #+#             */
/*   Updated: 2023/01/30 00:13:40 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	uns_n;

	uns_n = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		uns_n = -n;
	}
	if (uns_n > 9)
		ft_putnbr_fd(uns_n / 10, fd);
	ft_putchar_fd('0' + uns_n % 10, fd);
}
