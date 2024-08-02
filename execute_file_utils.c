/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_file_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:04:56 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/29 15:06:02 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_env_args(char **envp, char **args, int arg_zero)
{
	int		i;
	char	*trimmed_cmd;

	i = 0;
	if (!ft_strncmp(args[0], "/bin/", 5))
		trimmed_cmd = ft_strdup(&args[0][5]);
	else
		trimmed_cmd = ft_strdup(args[0]);
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
	if (arg_zero)
	{
		if (arg_zero == 2)
		{
			write(2, trimmed_cmd, ft_strlen(trimmed_cmd));
			write(2, ": Command not found.\n", 21);
		}
		free(args[0]);
	}
	free(trimmed_cmd);
	free(args);
	return (-1);
}

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

int	exec_com_fork(t_statement *temp, char **envp, char **args, t_mini *mini)
{
	int		i;
	int		status;

	i = 1;
	copy_temp(temp, i, args);
	mini->pid = fork();
	if (mini->pid == -1)
	{
		perror ("fork");
		free_env_args(envp, args, 1);
		exit (-1);
	}
	else if (mini->pid == 0)
	{
		if (execve(args[0], args, envp) == -1)
		{
			free_env_args(envp, args, 2);
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
	int		i;
	int		status;

	i = 0;
	copy_temp(temp, i, args);
	mini->pid = fork();
	if (mini->pid == -1)
	{
		perror ("fork");
		free_env_args(envp, args, 1);
		exit (-1);
	}
	else if (mini->pid == 0)
	{
		if (execve(args[0], args, envp) == -1)
		{
			free_env_args(envp, args, 2);
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
