/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:49:08 by ehedeman          #+#    #+#             */
/*   Updated: 2024/01/19 12:18:11 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_print(int n, int rt_length)
{
	char	*nbr;
	int		len;

	nbr = ft_itoa_print(n);
	if (!nbr)
		return (0);
	len = ft_strlen_print(nbr);
	rt_length += write(1, nbr, len);
	free(nbr);
	return (rt_length);
}
