/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_special_case.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:28:14 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/25 14:46:12 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_commands_rdr(t_statement *temp, t_mini *mini, int fd, int i)
{
	while (i < temp->argc && *temp->argv && fd != -1)
	{
		if (check_builtins(temp, mini, i))
			break ;
		if (!ft_strncmp(temp->argv[i], "./", 2)
			|| !ft_strncmp(temp->argv[i], "/", 1))
		{
			if (exec_file(temp, mini) == -1)
				return (-1);
			break ;
		}
		else// if (temp->operator != SKIP)
		{
			exec_command(temp, mini);
			return (0);
		}
		i++;
	}
	close(fd);
	return (0);
}

t_statement	*command_after_file_rdr(t_statement *temp, t_mini *mini)
{
	int	fd;

	while ((temp->operator == RDR_OUT_REPLACE
			|| temp->operator == RDR_OUT_APPEND) && temp)
	{
		fd = get_fd(temp);
		if (temp->next->operator == RDR_OUT_REPLACE
			|| temp->next->operator == RDR_OUT_APPEND)
			close(fd);
		else
		{
			temp = temp->next;
			break ;
		}
		temp = temp->next;
	}
	check_commands_rdr(temp, mini, fd, 1);
	temp = temp->next;
	return (temp);
}

int	check_command_after_file_rdr(t_statement *temp)
{
	if (!*temp->argv)
	{
		while ((temp->operator == RDR_OUT_REPLACE
			|| temp->operator == RDR_OUT_APPEND) && temp->next->next)
			temp = temp->next;
		if (temp->next->argc > 1)
			return (1);
	}
	return (0);
}
