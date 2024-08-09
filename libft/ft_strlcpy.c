/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:12:24 by ehedeman          #+#    #+#             */
/*   Updated: 2023/11/17 11:06:24 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		i;
	size_t		len;

	i = 0;
	len = ft_strlen(src);
	if (dstsize == 0)
		return (len);
	while (dstsize > i && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize <= len)
		dst[dstsize - 1] = '\0';
	else
		dst[i] = '\0';
	return (len);
}

// int main()
// {
//     char a[4];
//     char    b[5];
//     a[0] = 'a';
//     a[1] = 'a';
//     a[2] = 'a';
//     a[3] = '\0';
//     ft_strlcpy(b, a, 3);
// 	printf("%s", b);
//     return (0);
// }