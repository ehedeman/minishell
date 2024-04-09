/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 08:52:01 by ehedeman          #+#    #+#             */
/*   Updated: 2023/11/16 12:05:09 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	s_len;
	size_t	d_len;

	j = 0;
	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	i = d_len;
	if (dstsize == 0)
		return (s_len);
	if (dstsize < d_len)
		return (s_len + dstsize);
	else
	{
		while (src[j] && i < dstsize)
			dst[i++] = src[j++];
		if (i == dstsize && d_len < dstsize)
			dst[--i] = '\0';
		else
			dst[i] = '\0';
		return (s_len + d_len);
	}
}
