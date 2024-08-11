/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_just_pipes_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:58:41 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/11 16:07:33 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_involves_pipes(t_statement *parsed_input)
{
	t_statement	*current;

	current = parsed_input;
	while (current)
	{
		if (current->operator == PIPE)
			return (1);
		current = current->next;
	}
	return (0);
}

void	create_pipes(t_statement *current, int pipefd[])
{
	if (current->next && command_involves_pipes(current))
	{
		if (pipe(pipefd) == -1)
		{
			perror("Error: pipe could not be created");
			exit(EXIT_FAILURE);
		}
	}
}

void	wait_for_children_pipes(t_mini *mini)
{
	int	status;

	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			mini->exit_status = WEXITSTATUS(status);
	}
}
