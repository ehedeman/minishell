/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:07:02 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/05 14:10:19 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_for_children(t_mini *mini, pid_t pid)
{
	int	status;

	waitpid(pid, &status, WUNTRACED);//wait part stolen from exec_command lol
	if (WIFEXITED(status))
		mini->exit_status = WEXITSTATUS(status);
	else
		mini->exit_status = 1;
}

static void	child_process(t_statement *current, t_mini *mini, int pipe_fd[])
{
	redirect_stdout(mini, pipe_fd[1], 0);	//rlly unsure about this cuz i dont really get which end of the pipe's for what
	print_output_file(mini);
	reset_stdout(mini);
	//first the output-file gets printed into the write(?) end of the pipe
	//then all is reset
	redirect_stdin(mini, pipe_fd[0], 0);	//pipe as input
	set_temp_output_as_stdout(mini, 0);		//output file as output
	exec_command(current, mini, 0);			//do command
	reset_stdin(mini);						//reset all
	reset_stdout(mini);
	exit(EXIT_SUCCESS);						//yay done (in theory)
}

//trying to do it without node specific pipe's currently
static t_statement	*execute_pipeline(t_statement *current, t_mini *mini)
{
	int		pipe_fd[2];
	pid_t	pid;

	current = current->next; //command on left side of pipe was done 
								//earlier so skip to get to right side of pipe operator
	if (pipe(pipe_fd) == -1)
	{
		perror("Error: pipe could not be created");
		exit(EXIT_FAILURE);									//do we realy need exit here?
	}
	pid = fork();
	if (pid == 0)
		child_process(current, mini, pipe_fd);
	else if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE); //again, do we need exit here if the child process exits in child_process()?
	}
	else
		wait_for_children(mini, pid);
	reset_std(mini);
	return (current);
}

void	do_all_connected_pipes(t_statement *current, t_mini *mini)
{
	set_temp_output_as_stdout(mini, 0);//execute the command that has PIPE operator
	exec_command(current, mini, 0);
	reset_stdout(mini);
	while (current)
	{	
		if (current->operator == 5)
			current = execute_pipeline(current, mini);
		else
			current = current->next;
	}
	mini->current = current;
}