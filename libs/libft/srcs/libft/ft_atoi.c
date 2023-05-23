/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 13:22:29 by shinfray          #+#    #+#             */
/*   Updated: 2023/01/30 00:03:16 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	ft_atoi(const char *str)
{
	long int	n;
	long int	buff;
	char		sign;

	n = 0;
	sign = 1;
	while (ft_isspace(*str) != 0)
		++str;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	while (ft_isdigit(*str) != 0)
	{
		buff = n;
		n = n * 10 + *str++ - '0';
		if (n < buff && sign > 0)
			return (-1);
		if (n < buff && sign < 0)
			return (0);
	}
	return (n * sign);
}
