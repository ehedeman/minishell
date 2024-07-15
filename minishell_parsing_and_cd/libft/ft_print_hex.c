/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:10:04 by ehedeman          #+#    #+#             */
/*   Updated: 2024/01/19 12:18:12 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	ft_findlen_hex(unsigned int nbr)
{
	int	i;

	i = 0;
	while (nbr)
	{
		nbr /= 16;
		i++;
	}
	return (i);
}

static	int	ft_print_hex(const char *s, int rt_length, int len)
{
	while (len >= 0)
	{
		rt_length += write(1, &s[len], 1);
		len--;
	}
	return (rt_length);
}

int	ft_puthex_print(unsigned int nbr, const char *format, int rt_length)
{
	int		len;
	int		i;
	char	*num;

	if (nbr == 0)
		rt_length += write(1, "0", 1);
	else
	{
		i = 0;
		len = ft_findlen_hex(nbr);
		num = malloc(sizeof(char) * len + 1);
		if (!num)
			return (0);
		while (nbr)
		{
			num[i++] = format[nbr % 16];
			nbr /= 16;
		}
		num[i] = '\0';
		rt_length = ft_print_hex(num, rt_length, len -1);
		free(num);
	}
	return (rt_length);
}
