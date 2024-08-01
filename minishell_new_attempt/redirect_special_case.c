/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_special_case.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:28:14 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/01 15:43:16 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_commands_rdr(t_statement *current, t_mini *mini, int fd, int i)
{
	while (i < current->argc && *current->argv && fd != -1)
	{
		if (check_builtins(current, mini, i))
			break ;
		if (!ft_strncmp(current->argv[i], "./", 2)
			|| !ft_strncmp(current->argv[i], "/", 1))
		{
			if (exec_file(current, mini) == -1)
				return (-1);
			break ;
		}
		else// if (current->operator != SKIP)
		{
			exec_command(current, mini, 0);
			return (0);
		}
		i++;
	}
	close(fd);
	return (0);
}

t_statement	*command_after_file_rdr(t_statement *current, t_mini *mini)
{
	int	fd;

	while ((current->operator == RDR_OUT_REPLACE
			|| current->operator == RDR_OUT_APPEND) && current)
	{
		fd = get_fd(current);
		if (current->next->operator == RDR_OUT_REPLACE
			|| current->next->operator == RDR_OUT_APPEND)
			close(fd);
		else
		{
			current = current->next;
			break ;
		}
		current = current->next;
	}
	check_commands_rdr(current, mini, fd, 1);
	printf("test exit status bla%d\n", mini->exit_status);	
	current = current->next;
	return (current);
}

int	check_command_after_file_rdr(t_statement *current)
{
	if (!*current->argv)
	{
		while ((current->operator == RDR_OUT_REPLACE
			|| current->operator == RDR_OUT_APPEND) && current->next->next)
			current = current->next;
		if (current->next->argc > 1)
			return (1);
	}
	return (0);
}
