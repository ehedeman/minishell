/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:07:02 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/06 13:43:12 by ehedeman         ###   ########.fr       */
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
	// first the output-file gets printed into the write(?) end of the pipe
	// then all is reset
	redirect_stdin(mini, pipe_fd[0], 0);	//pipe as input
	set_temp_output_as_stdout(mini, 0);		//output file as output
	// yeah and for some reason in the child process the exec_command is only outputting bullshit
	// (nothing for wc -l and generally just looping around despite already having output the output)
	// wc -l info.txt | cat -e works but only after ctrl -c (if you comment out the set_temp_output in line 35
	// then it puts output before looping but thats just because the output gets printed after all operator-related
	// functions.)
	exec_command(current, mini, 0);			//do command
	reset_stdin(mini);						//reset all
	reset_stdout(mini);
	exit(EXIT_SUCCESS);						//yay done (in theory)
}

//trying to do it without node specific pipe's currently
static t_statement	*execute_pipeline(t_statement *current, t_mini *mini)
{
	pid_t	pid;

	current = current->next; //command on left side of pipe was done 
								//earlier so skip to get to right side of pipe operator
	if (pipe(current->pipe_fd) == -1)
	{
		perror("Error: pipe could not be created");
		exit(EXIT_FAILURE);									//do we realy need exit here?
	}
	pid = fork();
	if (pid == 0)
		child_process(current, mini, current->pipe_fd);//self explanatory i think
	else if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE); //again, do we need exit here if the child process exits in child_process()?
	}
	else
	{
		close(current->pipe_fd[0]);
		close(current->pipe_fd[1]);
		wait_for_children(mini, pid);
	}
	reset_std(mini);//just in case that it hasnt been reset yet idk
	return (current);
}
//INFO: redirect and reset must be called before anything else gets changed since they use a variable as condition
// thats responsible for the reset to be used. (reset sets the variable to -1 and redirect sets it to 0 or 1, reset only does
// the reset if the variable is 0 or 1.)

void	do_all_connected_pipes(t_statement *current, t_mini *mini)
{
	if (!current->id || (current->previous->operator > 4 //if we come from redirection then the current node is the file so we dont need to execute
			|| current->previous->operator < 1))
	{
		set_temp_output_as_stdout(mini, 0);//execute the command that has PIPE operator
		exec_command(current, mini, 0);
		reset_stdout(mini);
	}
	while (current && current->operator == PIPE)
	{	
		if (current->operator == 5 && (current->next->operator != 1 //if theres a redirection of input then thats priority to the pipe
			&& current->next->operator != 2))
			current = execute_pipeline(current, mini);
		else
			current = current->next;
	}
	if (current->operator == NONE) //nessecary cuz if its a RDR or whatever its on the right node but if its
		mini->current = current->next; //just a pipe at the end of a command then it'd end on the pipe. aka it goes into pipe twice
	else
		mini->current = current;
}
