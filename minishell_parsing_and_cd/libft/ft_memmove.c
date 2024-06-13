/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:05:22 by ehedeman          #+#    #+#             */
/*   Updated: 2023/11/17 11:10:23 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	alternatemove(char	*dst_copy, char *src_copy, int len)
{
	int	i;

	i = len -1;
	while (len > 0)
	{
		dst_copy[i] = src_copy[i];
		i--;
		len--;
	}
}

static	void	normalmove(char	*dst_copy, char *src_copy, int len)
{
	while (len > 0)
	{
		*dst_copy = *src_copy;
		src_copy++;
		dst_copy++;
		len--;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*src_copy;
	char	*dst_copy;

	if ((dst == src) || len == 0)
		return (dst);
	if (!dst && !src)
		return (0);
	src_copy = (char *)src;
	dst_copy = (char *)dst;
	if (src_copy < dst_copy)
	{
		alternatemove(dst_copy, src_copy, len);
	}
	else
	{
		normalmove(dst_copy, src_copy, len);
	}
	return (dst);
}

// int main()
// {
// 	char *b;
// 	char e[10];
// 	char d[10];
// 	e[0] = 'A';
//     e[1] = 'B';
//     e[2] = 'C';
//     e[3] = 'D';
//     e[4] = 'E';
//     e[5] = 'F';
//     e[6] = 'G';
//     e[7] = 'H';
//     e[8] = 'I';
//     e[9] = '\0';
// 	//printf("%s\n", &d[0]);
// 	d[0] = 'H';
// 	printf("%s\n", &e[9]);
// 	b = ft_memmove(d, e, 9);
// 	printf("%s", b);
// 	return (0);
// }
