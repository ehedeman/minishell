/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:12:06 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/26 15:06:16 by smatschu         ###   ########.fr       */
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
}

int	exit_arg(char *arg)
{
	int	exit_status;
	int	i;

	exit_status = 0;
	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			printf("exit: %s: numeric argument required\n", arg);
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
		exit_status = exit_arg(arg);
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
