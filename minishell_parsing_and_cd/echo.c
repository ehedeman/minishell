/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:28:15 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/15 19:02:34 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_mini *mini, t_statement *temp, int fd, int i)
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
		if(!ft_strcmp(temp->argv[i], "$?"))
			ft_putnbr_fd(mini->exit_status, fd);
		else if (!ft_strncmp(temp->argv[i], "'$", 2))
		{
			remove_quotes_main(temp, i);
			write(fd, temp->argv[i], ft_strlen(temp->argv[i]));
		}
		else
			write(fd, temp->argv[i], ft_strlen(temp->argv[i]));
		if (i < temp->argc -1)
				write(fd, " ", 1);
		i++;
	}
	if (!newline)
		write(fd, "\n", 1);
}