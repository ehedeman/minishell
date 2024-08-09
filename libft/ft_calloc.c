/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:53:40 by ehedeman          #+#    #+#             */
/*   Updated: 2023/11/23 12:41:19 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void		*a;
	char		*b;
	size_t		i;

	i = 0;
	a = (void *)malloc(size * count);
	if (a == NULL)
		return (a);
	b = (char *)a;
	while (i < size * count)
	{
		*b = 0;
		b++;
		i++;
	}
	return (a);
}
