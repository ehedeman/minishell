/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_file_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:04:56 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/06 14:48:23 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_temp(t_statement *temp, int i, char **args)
{
	while (i <= temp->argc)
	{
		if (i == temp->argc)
		{
			args[i] = NULL;
			break ;
		}
		args[i] = temp->argv[i];
		i++;
	}
}

static void	exec_child(char **args, char **envp, int file_or_command)
{
	if (execve(args[0], args, envp) == -1)
	{
	//	write(1, "TEST-1\n", 7);
	//	sleep(3);
		free_env_args(envp, args, file_or_command);
		if (errno == EACCES)
			exit (126);
		else if (errno == ENOENT)
			exit (127);
		else
			exit (1);
	}
	else
	{
	//	write(1, "TEST-2\n", 7); // for testing: output fd = 1 should be the output file, sleep(3) makes
	//	sleep(3);	// sure it doesnt get overwritten immideadly (same with the one above)
		exit(EXIT_SUCCESS); // last state was that sleep didnt do anything at all, therefor it never exited execve
	}
}

int	exec_com_fork(t_statement *temp, char **envp, char **args, t_mini *mini)
{
	int		status;

	copy_temp(temp, 1, args); // 1 because args[0] was set in exec_command
	mini->pid = fork();
	if (mini->pid == -1)
	{
		perror ("fork");
		free_env_args(envp, args, 1);
		exit (-1);
	}
	else if (mini->pid == 0)
		exec_child(args, envp, 2);
	else
	{
		waitpid(mini->pid, &status, WUNTRACED);
		if (WIFEXITED(status))
			mini->exit_status = WEXITSTATUS(status);
		else
			mini->exit_status = 1;
	}
	return (0);
}

int	exec_file_fork(t_statement *temp, char **envp, char **args, t_mini *mini)
{
	int		status;

	copy_temp(temp, 0, args); // 0 because args[0] was not set in exec_file
	mini->pid = fork();
	if (mini->pid == -1)
	{
		perror ("fork");
		free_env_args(envp, args, 1);
		exit (-1);
	}
	else if (mini->pid == 0)
		exec_child(args, envp, 3);
	else
	{
		waitpid(mini->pid, &status, 0);
		if (WIFEXITED(status))
			mini->exit_status = WEXITSTATUS(status);
		else
			mini->exit_status = 0;
	}
	return (0);
}
