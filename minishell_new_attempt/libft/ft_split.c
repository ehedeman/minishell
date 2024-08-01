/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:15:46 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/03 20:52:41 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	countc(char *s, int c)
{
	int		i;

	i = 0;
	while (*s)
	{
		while (*s == c)
		{
			s++;
			if (!*s)
				return (i);
		}
		i++;
		s = ft_strchr(s + 1, c);
		if (!s)
			return (i);
	}
	return (i);
}

static	int	findmsize(char *s, int c)
{
	int	i;

	i = 0;
	while (*s && *s != c)
	{
		s++;
		i++;
	}
	return (i);
}

static	int	ft_m(char *s, int c, char **a, int n)
{
	int		i;
	char	*str;

	i = 0;
	while (i < n && *s)
	{
		while (*s == c)
			s++;
		a[i] = malloc(sizeof(char) * findmsize(s, c) + 1);
		if (!a[i])
			return (0);
		str = a[i];
		while (*s != c && *s)
		{
			*str = *s;
			str++;
			s++;
		}
		*str = '\0';
		if (*s)
			s++;
		i++;
	}
	a[i] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**a;
	int		n;

	if (!s)
		return (0);
	if (!*s)
	{
		a = malloc(sizeof(char *) * 1);
		if (!a)
			return (0);
		a[0] = NULL;
		return (a);
	}
	n = countc((char *)s, c);
	a = malloc(sizeof(char *) * (n + 1));
	if (!a)
		return (0);
	if (ft_m((char *)s, c, a, n) == 1)
		return (0);
	return (a);
}

// int main()
// {
// 	char **a;
// 	a = ft_split("hello    hi    hello", '\0');
// 	printf("%s\n%s\n%s\n", a[0], a[1], a[2]);
// 	free(a[0]);
// 	free(a[1]);
// 	free(a[2]);
// 	free(a);
// 	return (0);
//  }