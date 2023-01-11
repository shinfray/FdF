/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:29:18 by shinfray          #+#    #+#             */
/*   Updated: 2022/11/11 01:16:47 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print(const char **format)
{
	const char *const	ptr = *format;
	int					len;

	len = 0;
	while (**format != '%' && **format != '\0')
		++(*format);
	len = write(1, ptr, *format - ptr);
	if (**format == '%')
		++(*format);
	return (len);
}

static char	ft_check_errors(int *count, int *temp)
{
	if (*count < *temp)
		return (-1);
	*temp = *count;
	return (0);
}

static int	ft_print_flags(const char *format, va_list *ap)
{
	if (*format == 's')
		return (ft_print_s(va_arg(*ap, char *)));
	else if (*format == 'c')
		return (ft_print_c(va_arg(*ap, int)));
	else if (*format == 'd' || *format == 'i')
		return (ft_print_d_i(va_arg(*ap, int)));
	else if (*format == 'u')
		return (ft_print_u(va_arg(*ap, unsigned int)));
	else if (*format == 'p')
		return (ft_print_p(va_arg(*ap, void *)));
	else if (*format == 'x' || *format == 'X')
		return (ft_print_x(va_arg(*ap, unsigned int), *format));
	else
		return (write(1, "%", 1));
}

static int	ft_parse_format(const char *format, va_list *ap)
{
	int	count;
	int	temp;

	count = 0;
	temp = 0;
	while (*format != '\0')
	{
		count += ft_print(&format);
		if (ft_check_errors(&count, &temp) < 0)
			return (-1);
		if (*format != '\0' && ft_strchr("scdiupxX%", (int)(*format)) != NULL)
		{
			count += ft_print_flags(format, ap);
			if (ft_check_errors(&count, &temp) < 0)
				return (-1);
		}
		else
			continue ;
		++format;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, format);
	count = ft_parse_format(format, &ap);
	va_end(ap);
	return (count);
}
