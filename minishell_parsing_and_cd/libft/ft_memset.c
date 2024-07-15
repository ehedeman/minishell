/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:46:55 by ehedeman          #+#    #+#             */
/*   Updated: 2023/11/15 09:56:48 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*b_copy;

	b_copy = (char *) b;
	while (len > 0)
	{
		*b_copy = (unsigned char) c;
		len--;
		b_copy++;
	}
	return (b);
}

// int	main(int argc, char **argv)
// {
// 	int		a;
// 	char	d[10];
// 	void	*c;

// 	a = argc;
// 	a = atoi(argv[1]);
// 	c = (void *) d;
// 	ft_memset(c, a, 10);
// 	printf("%s", d);
// 	memset(c, a, 10);
// 	printf("%s", d);
// 	return (0);
// }
