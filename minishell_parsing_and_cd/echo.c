/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:28:15 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/03 15:00:48 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_statement *temp, int fd, int i)
{
	bool newline;

	newline = false;
	i++;
	if (!ft_strncmp(temp->argv[i], "-n", 2) && !temp->argv[i][2])
	{
		newline = true;
		i++;
	}
	while (temp->argv[i])
	{
		write(fd, temp->argv[i], ft_strlen(temp->argv[i]));
		if (i < temp->argc -1)
			write(fd, " ", 1);
		i++;
	}
	if (!newline)
		write(fd, "\n", 1);
}