/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:04:06 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/01 15:04:31 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	establish_all_pipes(t_statement *first)
{
	t_statement *current;

	current = first;
	while (current)
	{
		if (operator == PIPE)
			create_pipes(current, current->pipefd);
		else
		{
			current->pipefd[0] = -1;
			current->pipefd[1] = -1;
		}
		current = current->next;
	}
}

void	close_all_pipes(t_statement *first)
{
	t_statement *current;

	current = first;
	while (current)
	{
		if (current->pipefd[0] > 0)
			close(current->pipefd[0]);
		if (current->pipefd[1] > 0)
			close(current->pipefd[1]);
		current = current->next;
	}
}
