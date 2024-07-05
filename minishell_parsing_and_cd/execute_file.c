/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:37:36 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/05 12:05:36 by ehedeman         ###   ########.fr       */
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

int	exec_file(t_statement *temp)
{
	char **args;
	char **envp;
	int status;
	pid_t pid;
	int	i;

	i = 0;
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
			return (main_error(EXECVE_ERR));
		}
	}
	else
		waitpid(pid, &status, 0);
	free(args);
	return (0);
}