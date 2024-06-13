/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:50:21 by ehedeman          #+#    #+#             */
/*   Updated: 2023/11/17 11:38:42 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char			*s_cpy;

	s_cpy = (unsigned char *)s;
	while (n && *s_cpy != (unsigned char)c)
	{
		s_cpy++;
		n--;
	}
	if (n)
		return ((void *)s_cpy);
	return (NULL);
}
