/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:28:15 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/14 17:59:52 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_statement *temp, int fd, int i)
{
	bool newline;

	newline = false;
	i++;
	if (temp->argv[i] && !ft_strncmp(temp->argv[i], "-n", 2) && !temp->argv[i][2])
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