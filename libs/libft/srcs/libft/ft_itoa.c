/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:25:37 by shinfray          #+#    #+#             */
/*   Updated: 2022/10/20 17:04:30 by simonhinf        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned char	ft_count_digit(int n)
{
	unsigned char	numb_digit;

	numb_digit = 1;
	if (n < 0)
		++numb_digit;
	while ((n / 10) != 0)
	{
		++numb_digit;
		n /= 10;
	}
	return (numb_digit);
}

static void	ft_set(char *const s, const unsigned int n, const unsigned char i)
{
	if (n > 9)
		ft_set(s, n / 10, i - 1);
	s[i] = n % 10 + '0';
}

char	*ft_itoa(int n)
{
	char			*s;
	unsigned int	uns_n;
	unsigned char	numb_digit;

	s = NULL;
	uns_n = n;
	numb_digit = ft_count_digit(n);
	if (n < 0)
		uns_n = -n;
	s = ft_calloc(numb_digit + 1, sizeof(*s));
	if (s == NULL)
		return (NULL);
	ft_set(s, uns_n, numb_digit - 1);
	s[numb_digit] = '\0';
	if (n < 0)
		*s = '-';
	return (s);
}
