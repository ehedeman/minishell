/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:28:15 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/01 13:42:13 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_statement *temp, int i)
{
	int	fd;

	fd = check_redirect(temp);
	i++;
	while (temp->argv[i])
	{
		write(fd, temp->argv[i], ft_strlen(temp->argv[i]));
		write(fd, " ", 1);
		i++;
	}
	write(fd, "\n", 1);
}