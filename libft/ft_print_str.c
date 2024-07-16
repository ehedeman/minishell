/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:43:55 by ehedeman          #+#    #+#             */
/*   Updated: 2024/01/19 12:18:08 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strlen_print(char *s)
{
	int	i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

int	ft_putstr_print(char *s, int rt_length)
{
	int	len;

	if (!s)
	{
		rt_length += write(1, "(null)", 6);
		return (rt_length);
	}
	else
	{
		len = ft_strlen_print(s);
		rt_length += write(1, s, len);
	}
	return (rt_length);
}

int	ft_putchar_print(int c, int rt_length)
{
	rt_length += write(1, &c, 1);
	return (rt_length);
}
