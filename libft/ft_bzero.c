/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:51:22 by ehedeman          #+#    #+#             */
/*   Updated: 2023/11/15 13:36:26 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*a;

	a = (char *) s;
	while (n != 0)
	{
		*a = 0;
		a++;
		n--;
	}
}

// int	main(int argc, char **argv)
// {
// 	int		a;
// 	char	d[10];
// 	void	*c;

// 	a = argc;
// 	a = atoi(argv[1]);
// 	c = (void *) d;
// 	ft_bzero(c, a);
// 	printf("%s", d);
// 	bzero(c, a);
// 	printf("%s", d);
// 	return (0);
// }
