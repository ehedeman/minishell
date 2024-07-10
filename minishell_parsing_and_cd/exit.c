/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:12:06 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/10 10:33:04 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_com_tab(t_mini *mini)
{
	t_statement	*temp;
	t_statement	*next;
	int	i;

	i = 0;
	temp = mini->com_tab;
	while(temp)
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

void	free_env(t_env_list *env)
{
	t_env_list	*temp;

	temp = env;
	while (temp)
	{
		if (temp->name)
			free(temp->name);
		if (temp->value)
			free(temp->value);
		temp = temp->next;
		free(env);
		env = temp;
	}
}

void	ft_exit(t_mini *mini)
{
	free_com_tab(mini);
	ft_env_lst_clear(mini->env, free);
	rl_clear_history();
	printf("Bye then :)\n");
	exit(0);
}

