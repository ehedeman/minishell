/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:12:06 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/30 12:36:36 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	exit_arg(char *arg, t_mini *mini)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			printf("exit: %s: numeric argument required\n", arg);
			mini->exit_status = 2;
			return (-1);
		}
		i++;
	}
	return (ft_atoi(arg));
}

int	ft_exit(t_mini *mini, char *arg)
{
	int	exit_status;

	exit_status = 0;
	if (arg)
	{
		exit_status = exit_arg(arg, mini);
		if (exit_status == -1)
			return (-1);
		printf("exit status: %i\n", exit_status);
	}
	free_com_tab(mini);
	ft_env_lst_clear(mini->env, free);
	free_history(&(mini->history));
	rl_clear_history();
	printf("Bye then :)\n");
	exit(exit_status);
}

int	check_exit(t_statement *temp, t_mini *mini, int i)
{
	if (!ft_strncmp(temp->argv[i], "exit", ft_strlen("exit") + 1))
	{
		if(!temp->argv[i + 1])
			ft_exit(mini, "0");
		if (temp->argv[i + 2])
		{
			printf("exit: too many arguments\n");
			mini->exit_status = 1;
			return (-1);
		}
		else if (temp->argv[i + 1])
		{
			ft_exit(mini, temp->argv[i + 1]);
			return (-1);
		}	
	}
	return (0);
}
