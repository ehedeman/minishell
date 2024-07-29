/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:15:14 by smatschu          #+#    #+#             */
/*   Updated: 2024/07/29 15:54:24 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// changed to check the command here, will create the pipe if needed.
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

void	child_process(t_statement *curr, t_mini *mini, int in_fd, int pipefd[])
{
	if (in_fd != STDIN_FILENO)
		redirect_stdin_pipe(in_fd); // redirect standard input if needed
	if (curr->next && command_involves_pipes(curr))
	{
		close(pipefd[0]); // close the read end of the pipe
		redirect_stdout_pipe(pipefd[1]); // redirect standard output to the pipe
	}
	exec_command(curr, mini, 0); // execute the command
	exit(EXIT_SUCCESS);
}

void	parent_process(t_statement *current, int *input_fd, int pipefd[])
{
	if (*input_fd != STDIN_FILENO)
		close(*input_fd); // Close the input fd if it's not standard input
	if (current->next && command_involves_pipes(current))
	{
		close(pipefd[1]); // Close the write end of the pipe
		*input_fd = pipefd[0]; // set the input fd to the read end of the pipe for the next command
	}
	else if (!current->next)
		close(pipefd[0]); // if it's the last command, close the read end of the pipe
}

// wait for all child processes to finish
void	wait_for_children(t_mini *mini)
{
	int	status;

	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			mini->exit_status = WEXITSTATUS(status);
	}
}

void	execute_pipeline(t_statement *commands, t_mini *mini)
{
	int			pipefd[2]; // this is to hold pipe file descriptors
	int			input_fd; // fd for input
	t_statement	*current; // pointer to the current command
	pid_t		pid; // process ID

	input_fd = STDIN_FILENO; // for the first command, input is STDIN
	current = commands;
	while (current != NULL)
	{
		create_pipes(current, pipefd); // set up pipes if needed
		pid = fork(); // create a new process
		if (pid == 0)
		{
		//	printf("child\n");
			child_process(current, mini, input_fd, pipefd);
		}
		else if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		parent_process(current, &input_fd, pipefd);
		if (current->operator != PIPE)
			break ;
		current = current->next; // go to the next command in the list
	}
	if (input_fd != STDIN_FILENO)
		close(input_fd); // close the last read end if it's not standard input
	wait_for_children(mini); // wait for all child processes to finish
}
