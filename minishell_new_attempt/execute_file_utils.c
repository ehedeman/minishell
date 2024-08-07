/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_file_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:04:56 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/07 18:43:33 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_array_size(char **array, int i)
{
	int	size;

	size = 0;
	while (array[i])
	{
		size++;
		i++;
	}
	return (size);
}

static void	copy_temp(t_exec *exec, int i, int j, t_mini *mini)
{
	while (i <= exec->current->argc)
	{
		if (i == exec->current->argc && !mini->additional_args)
		{
			exec->args[i] = NULL;
			break ;
		}
		else if (i == exec->current->argc && mini->additional_args)
			break ;
		exec->args[i] = exec->current->argv[j];
		i++;
		j++;
	}
	if (!mini->additional_args)
		return ;
	j = 0;
	while (mini->additional_args[j])
	{
		exec->args[i] = mini->additional_args[j];
		i++;
		j++;
	}
	exec->args[i] = NULL;
}

static void	exec_child(char **args, char **envp, int file_or_command)
{
	if (execve(args[0], args, envp) == -1)
	{
		free_env_args(envp, args, file_or_command);
		if (errno == EACCES)
			exit (126);
		else if (errno == ENOENT)
			exit (127);
		else
			exit (1);
	}
	else
		exit(EXIT_SUCCESS);
}

int	exec_com_fork(t_exec *exec, t_mini *mini, int i)
{
	int		status;

	copy_temp(exec, 1, i + 1, mini);
	mini->pid = fork();
	if (mini->pid == -1)
	{
		perror ("fork");
		free_env_args(exec->envp, exec->args, 1);
		exit (-1);
	}
	else if (mini->pid == 0)
		exec_child(exec->args, exec->envp, 2);
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

int	exec_file_fork(t_exec *exec, t_mini *mini, int i)
{
	int		status;

	copy_temp(exec, 0, i, mini);
	mini->pid = fork();
	if (mini->pid == -1)
	{
		perror ("fork");
		free_env_args(exec->envp, exec->args, 1);
		exit (-1);
	}
	else if (mini->pid == 0)
		exec_child(exec->args, exec->envp, 3);
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
