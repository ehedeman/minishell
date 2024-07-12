/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:37:36 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/12 11:26:58 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void print_p(char **parsed, int j)
// {
// 	int i = 0;
// 	printf("j: %i\n", j);
// 	while (parsed[i])
// 	{
// 		printf("print_p: %s\n", parsed[i]);
// 		i++;
// 	}
// 	printf("\n");
// }
int	exec_command(t_statement *temp)
{
	char **args;
	char **envp;
	int status;
	pid_t pid;
	int	i;

	i = 1;
	g_exec_file = 1; //tells program that theres a file being executed
	envp = NULL; //needs to be worked out -> with env function if done
	args = malloc(sizeof(char *) * (temp->argc + 1));
	args[0] = ft_strjoin("/bin/", temp->argv[0]);
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
	{
		free(args);
		return (main_error(FORK_ERR));
	}
	else if (pid == 0)
	{
		if (execve(args[0], args, envp) == -1)
		{
			free(args[0]);
			free(args);
			write(2, "Command not found.\n", 19);
			return (-1);
		}
	}
	else
		waitpid(pid, &status, 0);
	free(args[0]);
	free(args);
	g_exec_file = 0;
	return (0);
}

int	exec_file(t_statement *temp)
{
	char **args;
	char **envp;
	int status;
	pid_t pid;
	int	i;

	i = 0;
	g_exec_file = 1;
	envp = NULL; //needs to be worked out -> with env function if done
	args = malloc(sizeof(char *) * (temp->argc + 1));
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
	{
		free(args);
		return (main_error(FORK_ERR));
	}
	else if (pid == 0)
	{
		if (execve(args[0], args, envp) == -1)
		{
			free(args);
			write(2, strerror(errno), ft_strlen(strerror(errno)));
			write(1, "\n", 1);
			return (-1);
		}
	}
	else
		waitpid(pid, &status, 0);
	free(args);
	g_exec_file = 0;
	return (0);
}