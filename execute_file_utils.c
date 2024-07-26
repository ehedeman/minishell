/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_file_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:04:56 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/26 15:15:58 by smatschu         ###   ########.fr       */
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
			printf("%s: Command not found.\n", trimmed_cmd);
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
		perror ("fork exec_com_fork");
		free_env_args(envp, args, 1);
		exit (-1);
	}
	else if (mini->pid == 0)
	{
		printf("com_fork Executing command %s\n", args[0]);
		if (execve(args[0], args, envp) == -1)
		{
			perror("execve exec_com_fork");
			free_env_args(envp, args, 2);
			if (errno == EACCES)
				exit (126);
			else if (errno == ENOENT)
				exit (127);
			else
				exit (1);
		}
	}
	else
	{
		waitpid(mini->pid, &status, 0);
		if (WIFEXITED(status))
            mini->exit_status = WEXITSTATUS(status);
        else
            mini->exit_status = 1;
		printf("com_fork File %s executed with exit status %d\n", args[0], mini->exit_status);
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
		perror ("fork exec_file_fork");
		free_env_args(envp, args, 1);
		exit (-1);
	}
	else if (mini->pid == 0)
	{
		printf("file_fork Executing file %s\n", args[0]);
		if (execve(args[0], args, envp) == -1)
		{
			perror("execve exec_file_fork");
			free_env_args(envp, args, 2);
			if (errno == EACCES)
				exit (126);
			else if (errno == ENOENT)
				exit (127);
			else
				exit (1);
		}
	}
	else
	{
		waitpid(mini->pid, &status, 0);
		if (WIFEXITED(status))
            mini->exit_status = WEXITSTATUS(status);
        else
            mini->exit_status = 1;
		printf("file _fork File %s executed with exit status %d\n", args[0], mini->exit_status);
	}
	return (0);
}
