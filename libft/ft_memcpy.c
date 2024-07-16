/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 08:52:39 by ehedeman          #+#    #+#             */
/*   Updated: 2023/11/17 11:09:13 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*src_copy;
	char	*dst_copy;

	if ((dst == src) || n == 0)
		return (dst);
	if (!dst && !src)
		return (0);
	dst_copy = (char *)dst;
	src_copy = (char *)src;
	while (n > 0)
	{
		*dst_copy = *src_copy;
		src_copy++;
		dst_copy++;
		n--;
	}
	return (dst);
}

//  int main()
//  {
//      char a[4];
//      char    b[5];
//      a[0] = 'a';
//      a[1] = 'a';
//      a[2] = 'a';
//      a[3] = '\0';
//      ft_memcpy((void *)0, (void *)0, 3);
//  	printf("%s", b);
//      return (0);
//  }
