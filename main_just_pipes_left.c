/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_just_pipes_left.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:43:55 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/11 16:11:28 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// redirect standart input to fd
static int	redirect_stdin_pipe(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
		return (-1);
	close(fd);
	return (0);
}

// redirect standart output to fd
static int	redirect_stdout_pipe(int fd)
{
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (-1);
	close(fd);
	return (0);
}

static void	child_process(t_statement *curr, t_mini *mini, \
	int in_fd, int pipefd[])
{
	if (in_fd != STDIN_FILENO)
		redirect_stdin_pipe(in_fd);
	if (curr->next && command_involves_pipes(curr))
	{
		close(pipefd[0]);
		redirect_stdout_pipe(pipefd[1]);
	}
	exec_command(curr, mini, 0);
	exit(EXIT_SUCCESS);
}

static void	parent_process(t_statement *current, int *input_fd, int pipefd[])
{
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	if (current->next && command_involves_pipes(current))
	{
		close(pipefd[1]);
		*input_fd = pipefd[0];
	}
	else if (!current->next)
		close(pipefd[0]);
}

void	do_just_pipes(t_statement *commands, t_mini *mini)
{
	int			input_fd;
	t_statement	*current;
	pid_t		pid;

	input_fd = STDIN_FILENO;
	current = commands;
	while (current != NULL)
	{
		create_pipes(current, current->pipe_fd);
		pid = fork();
		if (pid == 0)
			child_process(current, mini, input_fd, current->pipe_fd);
		else if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		parent_process(current, &input_fd, current->pipe_fd);
		if (current->operator != PIPE)
			break ;
		current = current->next;
	}
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	wait_for_children_pipes(mini);
}
