/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:24:21 by shinfray          #+#    #+#             */
/*   Updated: 2023/01/19 09:51:17 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_print_s(va_list *ap);
int	ft_print_c(va_list *ap);
int	ft_print_x(va_list *ap);
int	ft_print_upper_x(va_list *ap);
int	ft_print_u(va_list *ap);
int	ft_print_d_i(va_list *ap);
int	ft_print_p(va_list *ap);

#endif
