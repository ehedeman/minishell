/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_file_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:04:56 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/17 17:38:31 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_env_args(char **envp, char **args, int arg_zero)
{
	int		i;
	char	*trimmed_cmd;

	i = 0;
	trimmed_cmd = ft_strtrim((args[0]), "/bin/");
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
		free(trimmed_cmd);
		free(args[0]);
	}
	free(args);
	return (-1);
}

int	exec_com_fork(t_statement *temp, char **envp, char **args, pid_t pid)
{
	int		i;
	int		status;

	i = 1;
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
	pid = fork();
	if (pid == -1)
		exit(free_env_args(envp, args, 1));
	else if (pid == 0)
	{
		if (execve(args[0], args, envp) == -1)
			exit(free_env_args(envp, args, 2));
	}
	else
		waitpid(pid, &status, 0);
	return (0);
}

int	exec_file_fork(t_statement *temp, char **envp, char **args, pid_t pid)
{
	int		i;
	int		status;

	i = 0;
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
	pid = fork();
	if (pid == -1)
		exit(free_env_args(envp, args, 0));
	else if (pid == 0)
	{
		if (execve(args[0], args, envp) == -1)
			exit(free_env_args(envp, args, 2));
	}
	else
		waitpid(pid, &status, 0);
	return (0);
}
