/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:50:59 by ehedeman          #+#    #+#             */
/*   Updated: 2024/01/19 12:18:10 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	ft_findlen_ptr(unsigned long long ptr)
{
	int	i;

	i = 0;
	while (ptr)
	{
		ptr /= 16;
		i++;
	}
	return (i);
}

static	int	ft_print_ptr(const char *s, int rt_length, int len)
{
	while (len >= 0)
	{
		rt_length += write(1, &s[len], 1);
		len--;
	}
	return (rt_length);
}

int	ft_putptr_print(unsigned long long ptr, const char *format, int rt_length)
{
	char	*num;
	int		i;
	int		len;

	rt_length += write (1, "0x", 2);
	if (ptr == 0)
	{
		rt_length += write (1, "0", 1);
		return (rt_length);
	}
	len = ft_findlen_ptr(ptr);
	num = malloc(sizeof(char) * len + 1);
	i = 0;
	if (!num)
		return (0);
	while (ptr)
	{
		num[i++] = format[ptr % 16];
		ptr /= 16;
	}
	rt_length = ft_print_ptr(num, rt_length, len - 1);
	free(num);
	return (rt_length);
}
