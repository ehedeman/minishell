/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:50:18 by ehedeman          #+#    #+#             */
/*   Updated: 2023/11/22 16:55:18 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	a;

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n *= -1;
		}
		if (n < 10)
		{
			a = n + '0';
			write (fd, &a, 1);
		}
		else
		{
			ft_putnbr_fd(n / 10, fd);
			a = (n % 10) + '0';
			write(fd, &a, 1);
		}
	}
}

//int main()
//{
//	ft_putnbr_fd(-123087, 1);
//	return (0);
//}