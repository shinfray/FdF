/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 03:02:21 by shinfray          #+#    #+#             */
/*   Updated: 2022/11/11 01:18:05 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_s(char *s)
{
	if (s == NULL)
		return (write(1, "(null)", 6));
	else
		return (write(1, s, ft_strlen(s)));
}

char	ft_print_c(const int c)
{
	const unsigned char	u_c = (const unsigned char)c;

	return (write(1, &u_c, 1));
}

static void	ft_recurs(const unsigned int uns_num, int *len, int *error)
{
	unsigned char	c;

	if (uns_num > 9)
	{
		ft_recurs(uns_num / 10, len, error);
	}
	c = '0' + uns_num % 10;
	if (write(1, &c, 1) > 0)
		++(*len);
	else
		*error = -1;
}

int	ft_print_u(const unsigned int u)
{
	int	len;
	int	error;

	len = 0;
	error = 0;
	ft_recurs(u, &len, &error);
	return (len);
}

int	ft_print_d_i(const int num)
{
	unsigned int	uns_num;
	int				len;
	int				error;

	uns_num = num;
	len = 0;
	error = 0;
	if (num < 0)
	{
		if (write(1, "-", 1) > 0)
			++len;
		else
			return (-1);
		uns_num = -num;
	}
	ft_recurs(uns_num, &len, &error);
	if (error == -1)
		return (error);
	else
		return (len);
}
