/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:15:14 by smatschu          #+#    #+#             */
/*   Updated: 2024/07/19 11:07:40 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipe(int pipefd[])
{
	if (pipe(pipefd) == -1)
	{
		perror("Error: pipe could not be created");
		exit(EXIT_FAILURE);
	}
	return (0);
}

static int	redirect_stdin(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
		return (-1);
	close(fd);
	return (0);
}

static int	redirect_stdout(int fd)
{
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (-1);
	close(fd);
	return (0);
}

int	command_involves_pipes(t_statement *parsed_input)
{
	t_statement	*current;

	current = parsed_input;
	while (current != NULL)
	{
		if (current->operator == PIPE)
			return (1);
		current = current->next;
	}
	return (0);
}

void	execute_pipeline(t_statement *commands, t_mini *mini)
{
	int			pipefd[2];
	int			input_fd;
	t_statement	*current;
	pid_t		pid;

	input_fd = STDIN_FILENO; // for the first command, input is STDIN
	current = commands;
	while (current != NULL)
	{
		if (current->next && command_involves_pipes(current))
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		pid = fork();
		if (pid == 0)
		{	
			// child process
			if (input_fd != STDIN_FILENO)
				redirect_stdin(input_fd);
			if (current->next && command_involves_pipes(current))
			{
				close(pipefd[0]);
				redirect_stdout(pipefd[1]);
			}
			exec_command(current, mini);
			exit(EXIT_SUCCESS);
		}
		else if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		// parent process
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		if (current->next && command_involves_pipes(current))
		{
			close(pipefd[1]);
			input_fd = pipefd[0];
		}
		else if (!current->next)
			close(pipefd[0]); // if it's the last command, close the read end
		current = current->next;
	}
	// close the last read end if it's not STDIN
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	// wait for all children to finish
	while (wait(NULL) > 0)
	{
	}
}
