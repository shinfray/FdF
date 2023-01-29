/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 03:09:46 by shinfray          #+#    #+#             */
/*   Updated: 2023/01/19 09:13:38 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_hexa(size_t n, const char *base, int *len)
{
	unsigned char	c;

	if (n > 15)
	{
		ft_putnbr_hexa(n / 16, base, len);
		if (*len == -1)
			return ;
	}
	c = base[n % 16];
	if (write(1, &c, 1) < 0)
	{
		*len = -1;
		return ;
	}
	(*len)++;
}

int	ft_print_x(va_list *ap)
{
	const size_t	x = va_arg(*ap, unsigned int);
	int				len;

	len = 0;
	ft_putnbr_hexa(x, "0123456789abcdef", &len);
	return (len);
}

int	ft_print_upper_x(va_list *ap)
{
	const size_t	x = va_arg(*ap, unsigned int);
	int				len;

	len = 0;
	ft_putnbr_hexa(x, "0123456789ABCDEF", &len);
	return (len);
}

int	ft_print_p(va_list *ap)
{
	void	*p;
	int		len;

	len = 0;
	p = va_arg(*ap, void *);
	if (write(1, "0x", 2) < 0)
		return (-1);
	ft_putnbr_hexa((size_t)p, "0123456789abcdef", &len);
	if (len < 0)
		return (-1);
	return (len + 2);
}
