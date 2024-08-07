/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:07:02 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/07 21:44:51 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_for_children(t_mini *mini, pid_t pid)
{
	int	status;

	waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status))
		mini->exit_status = WEXITSTATUS(status);
	else
		mini->exit_status = 1;
}

/*
Pipe
								--------------------------
Output data	from previous		|                        |
flows in this direction ------->| pipe_fd[0] (read end)  | 
								|                        |
								| pipe_fd[1] (write end) | ---> Input data flows in this direction
								|                        |		for the next ou stdout
								--------------------------
*/
static void	child_process(t_statement *current, t_mini *mini, int pipe_fd[])
{
	redirect_stdout(mini, pipe_fd[1], 0);
	print_output_file(mini);
	reset_stdout(mini);
	redirect_stdin(mini, pipe_fd[0], 0);
	set_temp_output_as_stdout(mini, 0);
	exec_command(current, mini, 0);
	reset_stdin(mini);
	reset_stdout(mini);
	exit(EXIT_SUCCESS);
}

static t_statement	*execute_pipeline(t_statement *current, t_mini *mini)
{
	pid_t	pid;

	current = current->next;
	if (pipe(current->pipe_fd) == -1)
	{
		perror("Error: pipe could not be created");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
		child_process(current, mini, current->pipe_fd);
	else if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else
	{
		close(current->pipe_fd[0]);
		close(current->pipe_fd[1]);
		wait_for_children(mini, pid);
	}
	reset_std(mini);
	return (current);
}

void	do_all_connected_pipes(t_statement *current, t_mini *mini)
{
	if (!current->id || (current->previous->operator > 4 \
			|| current->previous->operator < 1))
	{
		set_temp_output_as_stdout(mini, 0);
		exec_command(current, mini, 0);
		reset_stdout(mini);
	}
	while (current && current->operator == PIPE)
	{	
		if (current->operator == 5 && (current->next->operator != 1 \
			&& current->next->operator != 2))
			current = execute_pipeline(current, mini);
		else
			current = current->next;
	}
	if (current->operator == NONE)
		mini->current = current->next;
	else
		mini->current = current;
}
