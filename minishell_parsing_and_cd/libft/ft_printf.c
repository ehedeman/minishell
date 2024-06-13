/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:27:12 by ehedeman          #+#    #+#             */
/*   Updated: 2024/01/25 12:08:02 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_findlength(int rt_length, char s, va_list arg_ptr)
{
	if (s == 'i' || s == 'd')
		rt_length = ft_putnbr_print(va_arg(arg_ptr, int), rt_length);
	else if (s == 'c')
		rt_length = ft_putchar_print(va_arg(arg_ptr, int), rt_length);
	else if (s == 's')
		rt_length = ft_putstr_print(va_arg(arg_ptr, char *), rt_length);
	else if (s == '%')
		rt_length = ft_putchar_print(s, rt_length);
	else if (s == 'x')
		rt_length = ft_puthex_print(va_arg(arg_ptr, unsigned int),
				"0123456789abcdef",
				rt_length);
	else if (s == 'X')
		rt_length = ft_puthex_print(va_arg(arg_ptr, unsigned int),
				"0123456789ABCDEF",
				rt_length);
	else if (s == 'p')
		rt_length = ft_putptr_print(va_arg(arg_ptr, unsigned long long),
				"0123456789abcdef", rt_length);
	else if (s == 'u')
		rt_length = ft_putunsigned_print(va_arg(arg_ptr, unsigned int),
				rt_length);
	return (rt_length);
}

int	ft_printf(const char *s, ...)
{
	va_list	arg_ptr;
	int		rt_length;
	int		i;

	va_start(arg_ptr, s);
	i = 0;
	rt_length = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			rt_length = ft_findlength(rt_length, s[i + 1], arg_ptr);
			i += 2;
		}
		else
		{
			rt_length += write (1, &s[i], 1);
			i++;
		}
	}
	va_end(arg_ptr);
	return (rt_length);
}
