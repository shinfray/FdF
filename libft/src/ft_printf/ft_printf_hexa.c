/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 03:09:46 by shinfray          #+#    #+#             */
/*   Updated: 2022/11/11 01:15:00 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_hexa(size_t n, const char *base, int *len, int *error)
{
	unsigned char	c;

	if (n > 15)
		ft_putnbr_hexa(n / 16, base, len, error);
	c = base[n % 16];
	if (write(1, &c, 1) > 0)
		++(*len);
	else
		*error = -1;
}

int	ft_print_x(const size_t x, const char flag)
{
	int	len;
	int	error;

	len = 0;
	error = 0;
	if (flag == 'x')
		ft_putnbr_hexa(x, "0123456789abcdef", &len, &error);
	if (flag == 'X')
		ft_putnbr_hexa(x, "0123456789ABCDEF", &len, &error);
	return (len);
}

int	ft_print_p(const void *const p)
{
	int	len;
	int	error;

	len = 2;
	error = 0;
	if (write(1, "0x", 2) < 0)
		return (-1);
	ft_putnbr_hexa((size_t)p, "0123456789abcdef", &len, &error);
	if (error == -1)
		return (error);
	else
		return (len);
}
