/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:32:13 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/07 22:06:01 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <fcntl.h>
# include <stdarg.h>
# include <limits.h>

int		ft_putunsigned_print(unsigned int n, int rt_length);
int		ft_putchar_print(int c, int rt_length);
int		ft_putstr_print(char *s, int rt_length);
int		ft_putptr_print(unsigned long long ptr, const char *format,
			int rt_length);
int		ft_putnbr_print(int n, int rt_length);
int		ft_puthex_print(unsigned int nbr, const char *format, int rt_length);
char	*ft_itoa_print(int n);
int		ft_strlen_print(char *s);
int		ft_printf(const char *s, ...);

#endif