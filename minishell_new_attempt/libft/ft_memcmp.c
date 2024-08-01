/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:06:24 by ehedeman          #+#    #+#             */
/*   Updated: 2023/11/23 12:35:38 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*s1_cpy;
	char	*s2_cpy;
	int		result;

	result = 0;
	s1_cpy = (char *)s1;
	s2_cpy = (char *)s2;
	while (n > 0)
	{
		if (*s1_cpy != *s2_cpy)
		{
			result = (unsigned char)*s1_cpy - (unsigned char)*s2_cpy;
			break ;
		}
		s1_cpy++;
		s2_cpy++;
		n--;
	}
	return (result);
}
