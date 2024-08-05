/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_print_output_file.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:20:16 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/04 19:30:31 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void free_args(char **args)
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

int	print_output_file(t_mini *mini)
{
//	int	i;
	int	status;
	char **args;
	char **envp;

//	i = 0;
	envp = NULL;
	args = malloc(sizeof(char *) * (2 + 1));
	args[0] = ft_strjoin("/bin/", "cat");
	args[1] = malloc(sizeof(char) * ft_strlen(".output_the_first_cuz_what_the_fuck") + 1);
	ft_strlcpy(args[1], ".output_the_first_cuz_what_the_fuck", ft_strlen(".output_the_first_cuz_what_the_fuck") + 1);
	args[2] = NULL;
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
	return(0);
}
