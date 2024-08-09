/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifty_shades_of_free.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:01:01 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/08 11:07:43 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_mode(int mode, char *trimmed_cmd, char **args)
{
	if (mode)
	{
		if (mode == 2)
		{
			write(2, trimmed_cmd, ft_strlen(trimmed_cmd));
			write(2, ": Command not found.\n", 21);
		}
		if (mode == 3)
		{
			write(2, trimmed_cmd, ft_strlen(trimmed_cmd));
			write(2, ": File not found.\n", 19);
		}
		free(args[0]);
	}
}

int	free_env_args(char **envp, char **args, int mode)
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
	free_mode(mode, trimmed_cmd, args);
	free(trimmed_cmd);
	free(args);
	return (-1);
}

void	free_com_tab(t_mini *mini)
{
	t_statement	*temp;
	t_statement	*next;
	int			i;

	i = 0;
	temp = mini->com_tab;
	while (temp)
	{
		next = temp->next;
		i = 0;
		while (temp->argv[i])
		{
			free(temp->argv[i]);
			i++;
		}
		free(temp->argv);
		free(temp);
		temp = next;
	}
	free(mini->input);
	mini->input = NULL;
}

void	free_input(char **input, int j)
{
	int	i;

	i = 0;
	if (j >= 0)
	{
		while (j >= 0)
		{
			free(input[j]);
			j--;
		}
		free(input);
		return ;
	}
	while (input[i])
	{
		free(input[i]);
		i++;
	}
	free(input[i]);
	free(input);
}

void	free_node_input(t_statement *temp, char **input)
{
	int	i;

	i = 0;
	while (i < temp->argc)
	{
		free(temp->argv[i]);
		i++;
	}
	free(temp->argv[i]);
	free(temp->argv);
	free(temp);
	if (!input)
		return ;
	free_input(input, -1);
}
