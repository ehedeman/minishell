/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:55:53 by ehedeman          #+#    #+#             */
/*   Updated: 2024/01/19 12:21:34 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	findsize(int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static	char	*negative(int n, char *a)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 1;
	ret = malloc(sizeof(char) * findsize(n) + 2);
	if (!ret)
		return (0);
	ret[0] = '-';
	while (n > 0)
	{
		a[i] = (n % 10) + '0';
		n = n / 10;
		i++;
	}
	i--;
	while (i >= 0)
	{
		ret[j] = a[i];
		i--;
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

static	char	*positive(int n, char *a)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	ret = malloc(sizeof(char) * findsize(n) + 1);
	if (!ret)
		return (0);
	while (n > 0)
	{
		a[i] = (n % 10) + '0';
		n = n / 10;
		i++;
	}
	i--;
	while (i >= 0)
	{
		ret[j] = a[i];
		i--;
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

static	char	*largestint(void)
{
	char	*ret;

	ret = malloc(sizeof(char) * 12);
	if (!ret)
		return (0);
	ret[0] = '-';
	ret[1] = '2';
	ret[2] = '1';
	ret[3] = '4';
	ret[4] = '7';
	ret[5] = '4';
	ret[6] = '8';
	ret[7] = '3';
	ret[8] = '6';
	ret[9] = '4';
	ret[10] = '8';
	ret[11] = '\0';
	return (ret);
}

char	*ft_itoa_print(int n)
{
	char	a[10];
	char	*ret;

	ret = a;
	if (n == -2147483648)
	{
		ret = largestint();
	}
	else if (n < 0)
	{
		ret = negative((n * -1), a);
	}
	else if (n > 0)
	{
		ret = positive(n, a);
	}
	else if (n == 0)
	{
		ret = malloc(sizeof(char) * 2);
		if (!ret)
			return (0);
		ret[0] = '0';
		ret[1] = '\0';
	}
	return (ret);
}

//int main()
//{
//	char	*a;
//	a = ft_itoa(-123);
//	printf("%s", a);
//	free(a);
//	return (0);
//}
