/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_print_output_file.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:20:16 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/06 13:02:29 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_args(char **args)
{
	free(args[0]);
	free(args[1]);
	free(args);
}

static void	child(char **args, char **envp)
{
	if (execve(args[0], args, envp) == -1)
	{
		free_args(args);
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

static int	allocate_args(char **args)
{
	args = malloc(sizeof(char *) * (2 + 1));
	if (!args)
		return (-1);
	args[0] = ft_strjoin("/bin/", "cat");
	if (!args[0])
		return (-1);
	args[1] = malloc(sizeof(char) * ft_strlen(".output") + 1);
	if (!args[1])
		return (-1);
	ft_strlcpy(args[1], ".output", ft_strlen(".output") + 1);
	args[2] = NULL;
}

int	print_output_file(t_mini *mini)
{
	int		status;
	char	**args;
	char	**envp;

	envp = NULL;
	mini->pid = fork();
	if (mini->pid == -1)
	{
		perror ("fork");
		free_args(args);
		exit (-1);
	}
	else if (mini->pid == 0)
		child(args, envp);
	else
	{
		waitpid(mini->pid, &status, WUNTRACED);
		if (WIFEXITED(status))
			mini->exit_status = WEXITSTATUS(status);
		else
			mini->exit_status = 1;
	}
	free_args(args);
	return (0);
}
