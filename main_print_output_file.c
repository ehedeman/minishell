/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_print_output_file.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:20:16 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/07 21:47:34 by smatschu         ###   ########.fr       */
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
		free_args(args);
	return ;
}

static char	**allocate_args(t_mini *mini)
{
	char	**args;
	mode_t	mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	mini->temp_output = open(mini->out_path, O_RDWR | O_CREAT, mode);
	close(mini->temp_output);
	args = malloc(sizeof(char *) * (2 + 1));
	if (!args)
		return (NULL);
	args[0] = ft_strjoin("/bin/", "cat");
	if (!args[0])
		return (NULL);
	args[1] = malloc(sizeof(char) * ft_strlen(mini->out_path) + 1);
	if (!args[1])
		return (NULL);
	ft_strlcpy(args[1], mini->out_path, ft_strlen(mini->out_path) + 1);
	args[2] = NULL;
	return (args);
}

int	print_output_file(t_mini *mini)
{
	char	**args;
	char	**envp;

	envp = NULL;
	args = allocate_args(mini);
	if (!args)
		return (-1);
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
		wait(&mini->pid);
	free_args(args);
	return (0);
}
