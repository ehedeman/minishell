/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:38:14 by ehedeman          #+#    #+#             */
/*   Updated: 2024/01/19 12:18:07 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	ft_findlen_un(unsigned int nbr)
{
	int	i;

	i = 0;
	while (nbr)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

static	int	ft_print_u(const char *s, int rt_length, int len)
{
	while (len >= 0)
	{
		rt_length += write(1, &s[len], 1);
		len--;
	}
	return (rt_length);
}

int	ft_putunsigned_print(unsigned int n, int rt_length)
{
	char	*num;
	int		i;
	int		len;

	i = 0;
	if (n == 0)
		rt_length += write(1, "0", 1);
	else
	{
		len = ft_findlen_un(n);
		num = malloc(sizeof(char) * len + 1);
		if (!num)
			return (0);
		while (n)
		{
			num[i] = (n % 10) + '0';
			n /= 10;
			i++;
		}
		num[i] = '\0';
		rt_length = ft_print_u(num, rt_length, len -1);
		free(num);
	}
	return (rt_length);
}
