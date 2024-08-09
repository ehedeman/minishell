/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:32:12 by ehedeman          #+#    #+#             */
/*   Updated: 2023/11/16 12:05:22 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

//int	main(void)
//{
//	signed int	result;
//	char a[9] = "hello you";
//	char b[11] = "hello world";
//	result = ft_strncmp(a, b, 8);
//	printf("Test 1: %i \n", result);
//	char c[] = "";
//	char d[11] = "gow are you";
//	result = ft_strncmp(c, d, 9);
//	printf("Test 2: %i", result);
//}
