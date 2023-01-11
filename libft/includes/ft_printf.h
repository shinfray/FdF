/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:24:21 by shinfray          #+#    #+#             */
/*   Updated: 2023/01/11 16:48:06 by shinfray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

int		ft_printf(const char *format, ...);
int		ft_print_s(char *s);
char	ft_print_c(const int c);
int		ft_print_x(const size_t x, const char flag);
int		ft_print_u(const unsigned int u);
int		ft_print_d_i(const int num);
int		ft_print_p(const void *const p);
void	ft_putnbr_hexa(size_t n, const char *base, int *len, int *error);

#endif
